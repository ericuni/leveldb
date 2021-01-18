cc_library(
  name = 'skiplist',
  hdrs = 'skiplist.h',
  deps = [
    '//util:arena',
  ],
)

cc_test(
  name = 'skiplist_test',
  srcs = 'skiplist_test.cc',
  deps = [
    ':skiplist',
    '//util:testutil',
    '//util:hash',
    '//util:env',
  ],
)

cc_test(
  name = 'dbformat_test',
  srcs = 'dbformat_test.cc',
  deps = [
    '//:leveldb',
  ]
)

cc_test(
  name = 'memtable_test',
  srcs = 'memtable_test.cc',
  deps = [
    '//:leveldb',
  ],
)

cc_test(
  name = 'write_batch_test',
  srcs = 'write_batch_test.cc',
  deps = [
    '//:leveldb',
  ]
)

cc_library(
  name = 'log',
  hdrs = [
    'log_reader.h',
    'log_writer.h',
  ],
  srcs = [
    'log_reader.cc',
    'log_writer.cc',
  ],
  deps = [
    '//util:status',
    '//util:crc32c',
    '//util:env',
  ]
)

cc_test(
  name = 'log_test',
  srcs = 'log_test.cc',
  deps = [
    ':log',
    '//util:crc32c',
  ],
)

cc_test(
  name = 'version_edit_test',
  srcs = 'version_edit_test.cc',
  deps = [
    '//:leveldb',
  ]
)

cc_test(
  name = 'filename_test',
  srcs = 'filename_test.cc',
  deps = [
    '//:leveldb',
  ]
)
