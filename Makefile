#
# Data Processor v1.1
# A Pebble library for extracting elements from a delimited string.
# http://smallstoneapps.github.io/data-processor/
#
# ----------------------
#
# The MIT License (MIT)
#
# Copyright © 2014 Matthew Tole
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
# --------------------
#
# Makefile
#

CC=gcc
ifeq ($(TRAVIS), true)
CFLAGS=
else
CFLAGS=-std=c11
endif
CINCLUDES=-I tests/include/ -I tests/ -I src/

TEST_FILES=tests/data-processor.c
SRC_FILES=src/data-processor.c
TEST_EXTRAS=

all: test

test:
	$(CC) $(CFLAGS) $(CINCLUDES) $(TEST_FILES) $(SRC_FILES) $(TEST_EXTRAS) -o tests/run
	tests/run || (echo 'Data Processor tests failed' | terminal-notifier; exit 1)
	@rm tests/run
	@printf "\x1B[0m"