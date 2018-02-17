#!/usr/bin/env bash

# Remove previous coverage files
rm -rf src/CMakeFiles/*
rm -rf tests/CMakeFiles/*
rm -rf coverage/index*
touch coverage/index.html

# Build and execute the tests
DEBUG_MODE=true cmake .
make
./tests/testsuite

# Generate the coverage report with some options
# 'Html' output with 'HtmlDetails'. 'Summary' at the end and to 'Output' file
gcovr -r $(pwd) --html --html-details -s \
--exclude 'Mocks' --exclude 'tests' \
-o "$(pwd)/coverage/index.html"
