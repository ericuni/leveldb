#include <glog/logging.h>
#include <gtest/gtest.h>

#include "leveldb/db.h"
#include "leveldb/filter_policy.h"
#include "leveldb/options.h"

TEST(iterate, ex) {
  leveldb::Options options;
  options.create_if_missing = true;
  options.filter_policy = leveldb::NewBloomFilterPolicy(10);

  std::string path = "/root/git/leveldb/learn/db";
  LOG(INFO) << "path : " << path;

  leveldb::DB* db = nullptr;
  auto status = leveldb::DB::Open(options, path, &db);
  ASSERT_TRUE(status.ok()) << status.ToString();

  leveldb::ReadOptions read_options;
  auto it = db->NewIterator(read_options);
  it->SeekToFirst();

  auto count = 0;
  while (it->Valid()) {
    auto key = it->key();
    auto value = it->value();
    LOG(INFO) << key.ToString() << " -> " << value.ToString();

    it->Next();
    ++count;
    if (count >= 5) {
      break;
    }
  }
  LOG(INFO) << "kv count: " << count;

  delete it;
  delete db;
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
