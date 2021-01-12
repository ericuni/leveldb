#include <glog/logging.h>
#include <gtest/gtest.h>
#include "db/dbformat.h"
#include "db/memtable.h"

namespace leveldb {

class MemTableTest : public testing::Test {
 protected:
  void SetUp() {
    InternalKeyComparator comparator(BytewiseComparator());
    table_ = new MemTable(comparator);
    table_->Ref();
  }

  void TearDown() {
    table_->Unref();
  }

 protected:
  MemTable* table_ = nullptr;
};

TEST_F(MemTableTest, AddAndGet) {
  std::string key = "key";
  std::string value = "value";
  SequenceNumber seq = 100;
  table_->Add(seq, kTypeValue, key, value);

  std::unique_ptr<LookupKey> lookup_key;
  auto ok = false;
  std::string found;
  Status status;

  // same key with variant seqs
  {
    // exact seq
    lookup_key = std::make_unique<LookupKey>(key, seq);
    ok = table_->Get(*lookup_key, &found, &status);
    ASSERT_TRUE(ok);
    ASSERT_TRUE(status.ok());
    ASSERT_EQ(value, found);

    // [key, seq + 1] < [key, seq]
    found.clear();
    lookup_key = std::make_unique<LookupKey>(key, seq + 1);
    ok = table_->Get(*lookup_key, &found, &status);
    ASSERT_TRUE(ok);
    ASSERT_TRUE(status.ok());
    ASSERT_EQ(value, found);

    // [key, seq] < [key, seq - 1]
    found.clear();
    lookup_key = std::make_unique<LookupKey>(key, seq - 1);
    ok = table_->Get(*lookup_key, &found, &status);
    ASSERT_FALSE(ok);
  }

  // lookup key < key
  {
    lookup_key = std::make_unique<LookupKey>(Slice(key.c_str(), key.size() - 1), seq);
    ok = table_->Get(*lookup_key, &found, &status);
    ASSERT_FALSE(ok);
  }

  // lookup key > key
  {
    lookup_key = std::make_unique<LookupKey>(key + "plus", seq);
    ok = table_->Get(*lookup_key, &found, &status);
    ASSERT_FALSE(ok);
  }
}

TEST_F(MemTableTest, Delete) {
  std::string key = "key";
  std::string value = "value";
  SequenceNumber seq = 100;
  table_->Add(seq, kTypeDeletion, key, value);

   std::unique_ptr<LookupKey> lookup_key;
  auto ok = false;
  std::string found;
  Status status;

  // same key with variant seqs
  {
    // exact seq
    lookup_key = std::make_unique<LookupKey>(key, seq);
    ok = table_->Get(*lookup_key, &found, &status);
    ASSERT_TRUE(ok);
    ASSERT_TRUE(status.IsNotFound());

    // [key, seq + 1] < [key, seq]
    found.clear();
    lookup_key = std::make_unique<LookupKey>(key, seq + 1);
    ok = table_->Get(*lookup_key, &found, &status);
    ASSERT_TRUE(ok);
    ASSERT_TRUE(status.IsNotFound());

    // [key, seq] < [key, seq - 1]
    found.clear();
    lookup_key = std::make_unique<LookupKey>(key, seq - 1);
    ok = table_->Get(*lookup_key, &found, &status);
    ASSERT_FALSE(ok);
  }

   // lookup key < key
  {
    lookup_key = std::make_unique<LookupKey>(Slice(key.c_str(), key.size() - 1), seq);
    ok = table_->Get(*lookup_key, &found, &status);
    ASSERT_FALSE(ok);
  }

  // lookup key > key
  {
    lookup_key = std::make_unique<LookupKey>(key + "plus", seq);
    ok = table_->Get(*lookup_key, &found, &status);
    ASSERT_FALSE(ok);
  }
}

TEST_F(MemTableTest, Iterate) {
  SequenceNumber seq = 100;
  for (auto i = 0; i < 3; ++i) {
    auto key = "key" + std::to_string(i);
    auto value = "value" + std::to_string(i);
    for (auto j = -1; j <= 1; ++j) {
      table_->Add(seq + j, kTypeValue, key, value);
      table_->Add(seq + j, kTypeDeletion, key, value);
    }
  }
  auto* iterator = table_->NewIterator();
  iterator->SeekToFirst();
  while (iterator->Valid()) {
    auto key = iterator->key();
    ParsedInternalKey internal_key;
    auto ok = ParseInternalKey(key, &internal_key);
    ASSERT_TRUE(ok);
    LOG(INFO) << internal_key.DebugString() << " -> " << iterator->value().ToString();

    iterator->Next();
  }

  LOG(WARNING) << "seek key1 result";
  iterator->Seek("key1");
  while (iterator->Valid()) {
    auto key = iterator->key();
    ParsedInternalKey internal_key;
    auto ok = ParseInternalKey(key, &internal_key);
    ASSERT_TRUE(ok);
    LOG(INFO) << internal_key.DebugString() << " -> " << iterator->value().ToString();

    iterator->Next();
  }
  delete iterator;
}

}  // namespace leveldb
