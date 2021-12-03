#!/bin/zsh

cd ../build
make -j 30
cd -
bazel build :all
