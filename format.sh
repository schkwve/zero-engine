#!/usr/bin/env bash

find . -name "*.c" -o -name "*.h" | xargs clang-format -i