#include <glog/logging.h>
#include <gtest/gtest.h>
#include "leveldb/iterator.h"

namespace leveldb {

class IteratorTest : public testing::Test {
 protected:
  void TearDown() {
    if (iterator_) {
      delete iterator_;
    }
  }

 protected:
  Iterator* iterator_ = nullptr;
};

static void CleanUp(void* arg1, void *arg2) {
  LOG(INFO) << "cleanup " << reinterpret_cast<const char*>(arg1) << " and " << reinterpret_cast<const char*>(arg2);
}

static void CleanUp1(void* arg1, void *arg2) {
  LOG(INFO) << "cleanup";
}

TEST_F(IteratorTest, CleanUpChain) {
  iterator_ = NewEmptyIterator();
  iterator_->RegisterCleanup(CleanUp1, nullptr, nullptr);
  auto* arg1 = const_cast<void*>(static_cast<const void*>("msg1"));
  auto* arg2 = const_cast<void*>(static_cast<const void*>("msg2"));
  iterator_->RegisterCleanup(CleanUp, arg1, arg2);
}

}  // namespace leveldb
