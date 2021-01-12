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

cc_library(
  name = 'dbformat',
  hdrs = 'dbformat.h',
  srcs = 'dbformat.cc',
  deps = [
    '//util:coding',
    '//util:filter_policy',
    '//util:comparator',
  ]
)

cc_test(
  name = 'dbformat_test',
  srcs = 'dbformat_test.cc',
  deps = [
    ':dbformat',
  ]
)

cc_library(
  name = 'memtable',
  hdrs = 'memtable.h',
  srcs = 'memtable.cc',
  deps = [
    ':skiplist',
    ':dbformat',
    '//table:iterator',
  ]
)

cc_test(
  name = 'memtable_test',
  srcs = 'memtable_test.cc',
  deps = [
    ':memtable',
    ':dbformat',
  ],
)

cc_library(
  name = 'write_batch',
  hdrs = 'write_batch.h',
  srcs = 'write_batch.cc',
  deps = [
    ':memtable',
    ':dbformat',
  ],
)

cc_test(
  name = 'write_batch_test',
  srcs = 'write_batch_test.cc',
  deps = [
    ':write_batch',
    ':memtable',
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

cc_library(
  name = 'version_edit',
  hdrs = 'version_edit.h',
  srcs = 'version_edit.cc',
  deps = [
    ':dbformat',
    '//util:status',
  ]
)

cc_test(
  name = 'version_edit_test',
  srcs = 'version_edit_test.cc',
  deps = [
    ':version_edit',
  ]
)

cc_test(
  name = 'db_impl_test',
  srcs = 'db_impl_test.cc',
  deps = [
  ]
)

