cc_library(
  name = 'status',
  hdrs = 'leveldb/status.h',
  srcs = 'status.cc',
)

cc_test(
  name = 'status_test',
  srcs = 'status_test.cc',
  deps = [
    ':status',
  ]
)

cc_library(
  name = 'coding',
  hdrs = 'util/coding.h',
  srcs = 'coding.cc',
)

cc_test(
  name = 'coding_test',
  srcs = 'coding_test.cc',
  deps = [
    ':coding',
  ]
)

cc_library(
  name = 'crc32c',
  hdrs = 'crc32c.h',
  srcs = 'crc32c.cc',
)

cc_test(
  name = 'crc32c_test',
  srcs = 'crc32c_test.cc',
  deps = [
    ':crc32c',
  ]
)

cc_test(
  name = 'random_test',
  srcs = 'random_test.cc',
  deps = [
    '#glog',
  ]
)

cc_library(
  name = 'hash',
  hdrs = 'hash.h',
  srcs = 'hash.cc',
  deps = [
    ':coding',
  ],
)

cc_test(
  name = 'hash_test',
  srcs = 'hash_test.cc',
  deps = [
    ':hash',
  ],
)

cc_library(
  name = 'env',
  hdrs = 'leveldb/env.h',
  srcs = [
    'env.cc',
    'env_posix.cc',
  ],
  deps = [
    ':status',
    '#pthread',
  ],
)

cc_test(
  name = 'env_test',
  srcs = 'env_test.cc',
  deps = [
    ':env',
    ':testutil',
  ],
)

cc_library(
  name = 'histogram',
  hdrs = 'histogram.h',
  srcs = 'histogram.cc',
)

cc_library(
  name = 'options',
  hdrs = 'leveldb/options.h',
  srcs = 'options.cc',
  deps = [
    ':comparator',
    ':env',
  ]
)

cc_library(
  name = 'comparator',
  hdrs = 'leveldb/comparator.h',
  srcs = 'comparator.cc',
  deps = [
    ':logging',
  ]
)

cc_test(
  name = 'comparator_test',
  srcs = 'comparator_test.cc',
  deps = [
    ':comparator',
  ],
)

cc_library(
  name = 'filter_policy',
  hdrs = 'leveldb/filter_policy.h',
  srcs = [
    'filter_policy.cc',
  ]
)

cc_library(
  name = 'bloom',
  hdrs = [],
  srcs = 'bloom.cc',
  deps = [
    ':filter_policy',
    ':hash',
  ]
)

cc_test(
  name = 'bloom_test',
  srcs = 'bloom_test.cc',
  deps = [
    ':bloom',
    ':testutil',
    ':logging',
  ],
)

cc_library(
  name = 'cache',
  hdrs = 'leveldb/cache.h',
  srcs = 'cache.cc',
  deps = [
    ':hash',
  ],
)

cc_test(
  name = 'cache_test',
  srcs = 'cache_test.cc',
  deps = [
    ':cache',
  ],
)

cc_library(
  name = 'arena',
  hdrs = 'arena.h',
  srcs = 'arena.cc',
)

cc_test(
  name = 'arena_test',
  srcs = 'arena_test.cc',
  deps = [
    ':arena',
  ],
)

cc_library(
  name = 'testutil',
  hdrs = 'testutil.h',
  srcs = 'testutil.cc',
  deps = [
    '#gmock',
  ],
)

cc_library(
  name = 'logging',
  hdrs = 'logging.h',
  srcs = 'logging.cc',
)

cc_test(
  name = 'logging_test',
  srcs = 'logging_test.cc',
  deps = [
    ':logging',
  ],
)

