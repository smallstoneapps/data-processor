CC=gcc
ifeq ($(TRAVIS), true)
CFLAGS=
else
CFLAGS=-std=c11
endif
CINCLUDES=-I tests/include/ -I tests/ -I include

TEST_FILES=tests/data-processor.c
SRC_FILES=src/c/data-processor.c
TEST_EXTRAS=

all: test

test:
	@$(CC) $(CFLAGS) $(CINCLUDES) $(TEST_FILES) $(SRC_FILES) $(TEST_EXTRAS) -o tests/run
	@ tests/run
	@rm tests/run
	@printf "\x1B[0m"
