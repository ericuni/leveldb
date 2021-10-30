load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")
package(default_visibility = ["//visibility:public"])

cmake(
  name = 'leveldb',
  lib_source = glob(["**"]),
  out_static_libs = ["libleveldb.a"],
)

#cc_library(
#  name = 'leveldb',
#  hdrs = glob(['leveldb/*.h', 'util/*.h', 'port/*.h', 'db/*.h', 'table/*.h']),
#  srcs = glob(
#    ['table/*.cc', 'db/*.cc', 'util/*.cc', 'port/*.cc'],
#    exclude=['*_test.cc', 'util/env_windows*.cc', "db/leveldbutil.cc"]),
#  includes = ["include"],
#  deps = [
#    ':init',
#  ],
#)

cc_library(
  name = 'init',
  hdrs = [],
  deps = [
    ':google',
  ],
)

cc_library(
  name = 'google',
  hdrs = [],
  deps = [
    '@com_google_glog//:glog',
    '@com_github_gflags_gflags//:gflags',
    '@com_google_gtest//:gtest',
  ],
)

cc_library(
  name = 'gtest',
  hdrs = [],
  deps = ['@com_google_gtest//:gtest_main'],
)

