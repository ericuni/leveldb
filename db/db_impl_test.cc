#include <glog/logging.h>
#include <gtest/gtest.h>
#include "leveldb/db.h"

namespace leveldb {

TEST(DBTest, Open) {
  Options options;
  options.create_if_missing = true;
  DB* db = nullptr;
  std::string name = "db";
  auto status = DB::Open(options, name, &db);
  ASSERT_TRUE(status.ok());
  delete(db);
}

}  // namespace leveldb
