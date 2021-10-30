#include <glog/logging.h>
#include <gtest/gtest.h>
#include "leveldb/comparator.h"
#include "leveldb/slice.h"

namespace leveldb {

class BytewiseComparatorTest : public testing::Test {
 protected:
  void SetUp() {
    comparator = BytewiseComparator();
  }
 protected:
  const Comparator* comparator;
};

TEST_F(BytewiseComparatorTest, Name) {
  ASSERT_STREQ("leveldb.BytewiseComparator", comparator->Name());
}

TEST_F(BytewiseComparatorTest, Compare) {
  Slice x;
  Slice y;

  x = "abc";
  y = "abc";
  ASSERT_EQ(0, comparator->Compare(x, y));

  x = "abc";
  y = "abd";
  ASSERT_LT(comparator->Compare(x, y), 0);
  ASSERT_GT(comparator->Compare(y, x), 0);
}

TEST_F(BytewiseComparatorTest, FindShortestSeparator) {
  std::string start;
  Slice limit;

  start = "abc";
  limit = "abcxyz";
  comparator->FindShortestSeparator(&start, limit);
  ASSERT_EQ("abc", start);

  start = "abdc";
  comparator->FindShortestSeparator(&start, limit);
  ASSERT_EQ("abdc", start);

  start = "abcost";
  comparator->FindShortestSeparator(&start, limit);
  ASSERT_EQ("abcp", start);
}

TEST_F(BytewiseComparatorTest, FindShortSuccessor) {
  std::string key;

  key = "\xff\xab\xff\xff";
  comparator->FindShortSuccessor(&key);
  ASSERT_EQ("\xff\xac", key);

  key = "\xff\xff";
  comparator->FindShortSuccessor(&key);
  ASSERT_EQ("\xff\xff", key);
}

}  // namespace leveldb
