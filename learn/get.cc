#include <gflags/gflags.h>
#include <glog/logging.h>
#include <gtest/gtest.h>

#include "leveldb/db.h"
#include "leveldb/filter_policy.h"
#include "leveldb/options.h"

TEST(get, ex) {
  leveldb::Options options;
  options.create_if_missing = true;
  options.filter_policy = leveldb::NewBloomFilterPolicy(10);

  std::string path = "/root/git/leveldb/learn/db";
  LOG(INFO) << "path: " << path;

  std::string key = "key_100";
  LOG(INFO) << "key: " << key;
  leveldb::DB* db = nullptr;
  auto status = leveldb::DB::Open(options, path, &db);
  ASSERT_TRUE(status.ok()) << status.ToString();

  leveldb::ReadOptions read_options;
  std::string value;
  status = db->Get(read_options, key, &value);
  if (status.ok()) {
    LOG(INFO) << "found, and value is " << value;
  } else {
    LOG(INFO) << "not found " << status.ToString();
  }

  delete db;
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
