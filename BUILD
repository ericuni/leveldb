cc_library(
  name = 'leveldb',
  hdrs = [
    'leveldb/db.h',
  ],
  srcs = [
    'table/block_builder.cc',
    'table/block.cc',
    'table/filter_block.cc',
    'table/format.cc',
    'table/iterator.cc',
    'table/merger.cc',
    'table/table.cc',
    'table/table_builder.cc',
    'table/two_level_iterator.cc',
    'db/builder.cc',
    'db/dbformat.cc',
    'db/db_impl.cc',
    'db/db_iter.cc',
    'db/filename.cc',
    'db/memtable.cc',
    'db/table_cache.cc',
    'db/version_edit.cc',
    'db/version_set.cc',
    'db/write_batch.cc',
  ],
  deps = [
    '#glog',
    '//db:log',
    '//util:arena',
    '//util:bloom',
    '//util:cache',
    '//util:crc32c',
    '//util:coding',
    '//util:comparator',
    '//util:filter_policy',
    '//util:logging',
    '//util:options',
  ],
)
