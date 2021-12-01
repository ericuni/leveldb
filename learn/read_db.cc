#include <gflags/gflags.h>
#include <glog/logging.h>

#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/filter_policy.h"

DEFINE_string(path, "./db", "db path");
DEFINE_string(key, "key", "");

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
	auto it = db->NewIterator(read_options);
  it->Seek(FLAGS_key);
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

  delete it;
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
