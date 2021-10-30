#include <glog/logging.h>
#include <gtest/gtest.h>
#include "leveldb/options.h"
#include "table/block_builder.h"
#include "table/block.h"
#include "table/format.h"

namespace leveldb {

class BlockTest : public testing::Test {
 protected:
  void SetUp() {
    std::map<std::string, std::string> sorted_kvs;
    for (auto i = 0; i < 20; ++i) {
      std::string key = "key" + std::to_string(i);
      std::string value = "value" + std::to_string(i);
      sorted_kvs.insert({key, value});
    }

    builder_ = std::make_unique<BlockBuilder>(&options_);
    for (auto it = sorted_kvs.begin(); it != sorted_kvs.end(); ++it) {
      builder_->Add(it->first, it->second);
    }

    BlockContents content;
    content.data = builder_->Finish();;
    content.cachable = false;
    content.heap_allocated = false;
    block_ = std::make_unique<Block>(content);

    iterator_ = block_->NewIterator(options_.comparator);
  }

  void TearDown() {
    delete iterator_;
  }

 protected:
  std::unique_ptr<Block> block_;
  Iterator* iterator_;

 private:
  Options options_;
  std::unique_ptr<BlockBuilder> builder_;
};

TEST_F(BlockTest, Iterate) {
  // iterator asc
  std::vector<std::string> keys1;
  iterator_->SeekToFirst();
  while (iterator_->Valid()) {
    keys1.push_back(iterator_->key().ToString());
    iterator_->Next();
  }

  // iterator desc
  std::vector<std::string> keys2;
  iterator_->SeekToLast();
  while (iterator_->Valid()) {
    keys2.push_back(iterator_->key().ToString());
    iterator_->Prev();
  }
  std::reverse(keys2.begin(), keys2.end());

  ASSERT_EQ(keys1, keys2);
}

TEST_F(BlockTest, IteratorSeek) {
  // seek extract key
  iterator_->Seek("key11");
  ASSERT_TRUE(iterator_->Valid());
  ASSERT_EQ("key11", iterator_->key().ToString());

  // seek target < all key
  iterator_->Seek("key");
  ASSERT_TRUE(iterator_->Valid());
  ASSERT_EQ("key0", iterator_->key().ToString());

  // seek target > all key
  iterator_->Seek("kez");
  ASSERT_FALSE(iterator_->Valid());

  // seek target miss, but in this block range
  iterator_->Seek("key123");
  ASSERT_TRUE(iterator_->Valid());
  ASSERT_EQ("key13", iterator_->key().ToString());
}

TEST_F(BlockTest, IteratorBoundary) {
  iterator_->SeekToFirst();
  ASSERT_TRUE(iterator_->Valid());
  iterator_->Prev();
  ASSERT_FALSE(iterator_->Valid());

  iterator_->SeekToLast();
  ASSERT_TRUE(iterator_->Valid());
  iterator_->Next();
  ASSERT_FALSE(iterator_->Valid());
}

}  // namespace leveldb

