#include <gflags/gflags.h>
#include <glog/logging.h>

#include "leveldb/db.h"
#include "leveldb/filter_policy.h"
#include "leveldb/options.h"

DEFINE_string(path, "./db", "db path");
DEFINE_string(key, "key", "key_100");

namespace wcg {

int main() {
  leveldb::Options options;
  options.create_if_missing = true;
  options.filter_policy = leveldb::NewBloomFilterPolicy(10);

  leveldb::DB* db = nullptr;
  auto status = leveldb::DB::Open(options, FLAGS_path, &db);
  if (!status.ok()) {
    LOG(ERROR) << "open " << FLAGS_path << " error";
    return -1;
  }

  leveldb::ReadOptions read_options;
  std::string value;
  status = db->Get(read_options, FLAGS_key, &value);
  if (status.ok()) {
    LOG(INFO) << "found, and value is " << value;
  } else {
    LOG(INFO) << "not found " << status.ToString();
  }

  delete db;
  return 0;
}

}  // namespace wcg

int main(int argc, char* argv[]) {
  FLAGS_alsologtostderr = true;
  FLAGS_colorlogtostderr = true;
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);

  return wcg::main();
}
