#!/bin/bash

script_dir=$(dirname -- "$(readlink -f -- "$BASH_SOURCE")")

export CC=/usr/bin/clang
export CXX=/usr/bin/clang++
cmake ${script_dir}
