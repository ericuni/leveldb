cc_library(
  name = 'iterator',
  hdrs = [
    'leveldb/iterator.h',
    'iterator_wrapper.h',
  ],
  srcs = 'iterator.cc',
  deps = [
    '//util:status',
    '#glog',
  ]
)

cc_test(
  name = 'iterator_test',
  srcs = 'iterator_test.cc',
  deps = [
    ':iterator',
  ]
)

cc_library(
  name = 'two_level_iterator',
  hdrs = 'two_level_iterator.h',
  srcs = 'two_level_iterator.cc',
  deps = [
    ':iterator',
  ]
)

cc_library(
  name = 'format',
  hdrs = 'format.h',
  srcs = 'format.cc',
  deps = [
    '//util:coding',
    '//util:status',
    '//util:crc32c',
  ]
)

cc_library(
  name = 'block',
  hdrs = [
    'block.h',
  ],
  srcs = [
    'block_builder.cc',
    'block.cc',
    'filter_block.cc',
  ],
  deps = [
    ':iterator',
    '//util:coding',
    '//util:options',
    '//util:filter_policy',
    '//util:hash',
  ]
)

cc_test(
  name = 'block_test',
  srcs = 'block_test.cc',
  deps = [
    ':block',
    ':format',
  ]
)

cc_test(
  name = 'filter_block_test',
  srcs = 'filter_block_test.cc',
  deps = [
    ':block',
    '//util:logging',
    '//util:testutil',
  ]
)

cc_library(
  name = 'table',
  hdrs = 'leveldb/table.h',
  srcs = [
    'table.cc',
    'table_builder.cc',
  ],
  deps = [
    ':block',
    ':format',
    ':two_level_iterator',
    '//util:crc32c',
  ]
)

cc_test(
  name = 'table_test',
  srcs = 'table_test.cc',
  deps = [
    ':table',
    '//util:testutil',
  ]
)

