#include <cstdio>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <memory>
#include <random>

#include "leveldb/db.h"
#include "leveldb/env.h"
#include "leveldb/filter_policy.h"
#include "leveldb/options.h"

using namespace std::literals;

DEFINE_string(path, "/root/git/leveldb/learn/db", "db path");
DEFINE_int32(n, 20 * 10000, "number of records");

namespace wcg {

int main() {
  auto env = leveldb::Env::Default();
  if (env->FileExists(FLAGS_path)) {
    LOG(ERROR) << FLAGS_path << " exists";
    return 0;
  }

  leveldb::Options options;
  options.create_if_missing = true;
  options.filter_policy = leveldb::NewBloomFilterPolicy(10);

  leveldb::DB* db = nullptr;
  auto status = leveldb::DB::Open(options, FLAGS_path, &db);
  if (!status.ok()) {
    LOG(ERROR) << "open " << FLAGS_path << " error";
    return -1;
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distribution(1, 5);

  leveldb::WriteOptions writeOptions;
  auto max_len = 1024;
  auto key = std::make_unique<char[]>(max_len);
  auto value = std::make_unique<char[]>(max_len);
  for (auto i = 0; i < FLAGS_n; ++i) {
    snprintf(key.get(), max_len, "key_%d", i);
    snprintf(value.get(), max_len, "value_%d", i);

    if (distribution(gen) == 1) {
      status = db->Delete(writeOptions, key.get());
      if (!status.ok()) {
        LOG(ERROR) << "delete " << key.get() << " error";
        return -1;
      }
    }

    status = db->Put(writeOptions, key.get(), value.get());
    if (!status.ok()) {
      LOG(ERROR) << "put " << key.get() << " error";
      return -1;
    }

    if (distribution(gen) == 1) {
      status = db->Delete(writeOptions, key.get());
      if (!status.ok()) {
        LOG(ERROR) << "delete " << key.get() << " error";
        return -1;
      }
    }
  }

  delete db;
  delete options.filter_policy;
  return 0;
}

}  // namespace wcg

int main(int argc, char* argv[]) {
  // FLAGS_alsologtostderr = true;
  FLAGS_colorlogtostderr = true;
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);

  return wcg::main();
}
