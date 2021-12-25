#include <glog/logging.h>
#include <gtest/gtest.h>

#include "leveldb/db.h"
#include "leveldb/filter_policy.h"
#include "leveldb/options.h"

class ReadTest : public testing::Test {
 protected:
  static void SetUpTestSuite() {
    leveldb::Options options;
    options.create_if_missing = false;
    options.filter_policy = leveldb::NewBloomFilterPolicy(10);

    std::string path = "/root/git/leveldb/learn/db";
    LOG(INFO) << "path: " << path;

    auto status = leveldb::DB::Open(options, path, &db_);
    ASSERT_TRUE(status.ok()) << status.ToString();
  }

  static void TearDownTestSuite() {
    if (db_) {
      delete db_;
    }
  }

 protected:
  static leveldb::DB* db_;
};

leveldb::DB* ReadTest::db_ = nullptr;

TEST_F(ReadTest, get) {
  std::string key = "key_100";
  LOG(INFO) << "key: " << key;

  leveldb::ReadOptions read_options;
  std::string value;
  auto status = db_->Get(read_options, key, &value);
  if (status.ok()) {
    LOG(INFO) << "found, and value is " << value;
  } else {
    LOG(INFO) << "not found " << status.ToString();
  }
}

TEST_F(ReadTest, scan) {
  leveldb::ReadOptions read_options;
  auto it = db_->NewIterator(read_options);
  it->SeekToFirst();

  auto count = 0;
  while (it->Valid()) {
    auto key = it->key();
    auto value = it->value();

    LOG_IF(INFO, count < 5) << key.ToString() << " -> " << value.ToString();

    it->Next();
    ++count;
  }
  LOG(INFO) << "kv count: " << count;

  delete it;
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
