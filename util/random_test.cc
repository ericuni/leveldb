#include <glog/logging.h>
#include <gtest/gtest.h>
#include "util/random.h"

namespace leveldb {

class RandomTest : public testing::Test {
 protected:
  void SetUp() {
    rnd_ = std::make_unique<Random>(301);
  }

 protected:
  std::unique_ptr<Random> rnd_;
};

TEST_F(RandomTest, Next) {
  for (auto i = 0; i < 5; ++i) {
    LOG(INFO) << rnd_->Next();
  }
}

TEST_F(RandomTest, Skewed) {
  for (auto i = 0; i < 10; ++i) {
    LOG(INFO) << rnd_->Skewed(17);
  }
}

TEST_F(RandomTest, OneIn) {
  for (auto i = 0; i < 10; ++i) {
    LOG(INFO) << rnd_->OneIn(5);
  }
}

}  // namespace leveldb
