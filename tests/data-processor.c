/*

Data Processor v1.0
A Pebble library for extracting elements from a delimited string.
http://smallstoneapps.github.io/data-processor/

----------------------

The MIT License (MIT)

Copyright © 2014 Matthew Tole

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

--------------------

tests/data-processor.c

*/

#include "unit.h"
#include "../src/data-processor.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

int tests_run = 0;
int tests_passed = 0;
const int NUM_TESTS = 15;

static void before_each(void) {
  data_processor_deinit();
}

// The global state object should be available after init.
static char* test_init(void) {
  data_processor_init("", '|');
  mu_assert(data_processor_get_global() != NULL, "Global state does not exist.");
  return 0;
}

// The global state object should not be available until init.
static char* test_noinit(void) {
  mu_assert(data_processor_get_global() == NULL, "Global state exists when it shouldn't.");
  return 0;
}

// A single string should be extractable.
static char* test_global_single_string(void) {
  data_processor_init("Hello", '|');
  ProcessingState* state = data_processor_get_global();
  const char* str = data_processor_get_string(state);
  mu_assert(strcmp(str, "Hello") == 0, "Single string not extracted from global state");
  return 0;
}

// Several strings separated by delimiter should be extractable.
static char* test_global_multiple_strings(void) {
  data_processor_init("Hello|Hi|Hey||", '|');
  ProcessingState* state = data_processor_get_global();
  const char* str1 = data_processor_get_string(state);
  const char* str2 = data_processor_get_string(state);
  const char* str3 = data_processor_get_string(state);
  const char* str4 = data_processor_get_string(state);
  const char* str5 = data_processor_get_string(state);
  bool pass = strcmp(str1, "Hello") == 0;
  pass = pass && strcmp(str2, "Hi") == 0;
  pass = pass && strcmp(str3, "Hey") == 0;
  pass = pass && strcmp(str4, "") == 0;
  pass = pass && strcmp(str5, "") == 0;
  mu_assert(pass, "Multiple strings not extracted from global state");
  return 0;
}

// A single number should be extractable.
static char* test_global_single_number(void) {
  data_processor_init("1", '|');
  int num = data_processor_get_int(data_processor_get_global());
  mu_assert(1 == num, "Single number not extracted from global state");
  return 0;
}

// Multiple numbers should be extractable.
static char* test_global_multiple_numbers(void) {
  data_processor_init("1|55555|0", '|');
  ProcessingState* state = data_processor_get_global();
  int num1 = data_processor_get_int(state);
  int num2 = data_processor_get_int(state);
  int num3 = data_processor_get_int(state);
  mu_assert(1 == num1 && 55555 == num2 && 0 == num3, "Multiple numbers not extracted from global state");
  return 0;
}

// A single boolean should be extractable.
static char* test_global_single_boolean(void) {
  data_processor_init("1", '|');
  bool boolean = data_processor_get_bool(data_processor_get_global());
  mu_assert(true == boolean, "Single boolean not extracted from global state");
  return 0;
}

// Multiple booleans should be extractable.
static char* test_global_multiple_booleans(void) {
  data_processor_init("1|0|", '|');
  bool boolean1 = data_processor_get_bool(data_processor_get_global());
  bool boolean2 = data_processor_get_bool(data_processor_get_global());
  bool boolean3 = data_processor_get_bool(data_processor_get_global());
  mu_assert(true == boolean1 && false == boolean2 && false == boolean3, "Multipe booleans not extracted from global state");
  return 0;
}

// Mixed values should be extractable from the global state.
static char* test_global_mixed(void) {
  data_processor_init("8|This is a string!|0|6765444", '|');
  int num1 = data_processor_get_int(data_processor_get_global());
  char* string1 = data_processor_get_string(data_processor_get_global());
  bool boolean1 = data_processor_get_bool(data_processor_get_global());
  int num2 = data_processor_get_int(data_processor_get_global());
  mu_assert(8 == num1 && 0 == strcmp("This is a string!", string1) && false == boolean1 && 6765444 == num2, "Mixed values not extracted from global state");
  return 0;
}

// Mixed values should be extractable from a single local state.
static char* test_single_local_mixed(void) {
  ProcessingState* state = data_processor_create("8|This is a string!|0|6765444", '|');
  int num1 = data_processor_get_int(state);
  char* string1 = data_processor_get_string(state);
  bool boolean1 = data_processor_get_bool(state);
  int num2 = data_processor_get_int(state);
  mu_assert(8 == num1 && 0 == strcmp("This is a string!", string1) && false == boolean1 && 6765444 == num2, "Mixed values not extracted from global state");
  return 0;
}

// Mixed values should be simultaneously be extractable from multiple local states.
static char* test_multiple_local_mixed(void) {
  ProcessingState* state1 = data_processor_create("8|This is a string!", '|');
  ProcessingState* state2 = data_processor_create("0|6765444", '|');
  int num1 = data_processor_get_int(state1);
  bool boolean1 = data_processor_get_bool(state2);
  char* string1 = data_processor_get_string(state1);
  int num2 = data_processor_get_int(state2);
  mu_assert(8 == num1 && 0 == strcmp("This is a string!", string1) && false == boolean1 && 6765444 == num2, "Mixed values not extracted from global state");
  return 0;
}

// Mixed values should be simultaneously be extractable from the global and a local state.
static char* test_local_and_global_mixed(void) {
  ProcessingState* state1 = data_processor_create("8|This is a string!", '|');
  data_processor_init("0|6765444", '|');
  ProcessingState* state2 = data_processor_get_global();
  int num1 = data_processor_get_int(state1);
  bool boolean1 = data_processor_get_bool(state2);
  char* string1 = data_processor_get_string(state1);
  int num2 = data_processor_get_int(state2);
  mu_assert(8 == num1 && 0 == strcmp("This is a string!", string1) && false == boolean1 && 6765444 == num2, "Mixed values not extracted from global state");
  return 0;
}

// The count of a single subelement should be 1.
static char* test_count_single(void) {
  data_processor_init("Hello", '|');
  int count = data_processor_count(data_processor_get_global());
  mu_assert(1 == count, "Count of single subelement not calculated correctly");
  return 0;
}

// The count of multiple subelements should be equal to the number of subelements.
static char* test_count_multiple(void) {
  data_processor_init("Hello|Goodbye||", '|');
  int count = data_processor_count(data_processor_get_global());
  mu_assert(4 == count, "Count of multiple subelements not calculated correctly");
  return 0;
}

// The count of an empty string should be 0.
static char* test_count_none(void) {
  data_processor_init("", '|');
  int count = data_processor_count(data_processor_get_global());
  mu_assert(0 == count, "Count of zero subelements not calculated correctly");
  return 0;
}

static char* all_tests() {
  mu_run_test(test_init);
  mu_run_test(test_noinit);
  mu_run_test(test_global_single_string);
  mu_run_test(test_global_multiple_strings);
  mu_run_test(test_global_single_number);
  mu_run_test(test_global_multiple_numbers);
  mu_run_test(test_global_single_boolean);
  mu_run_test(test_global_multiple_booleans);
  mu_run_test(test_global_mixed);
  mu_run_test(test_single_local_mixed);
  mu_run_test(test_multiple_local_mixed);
  mu_run_test(test_local_and_global_mixed);
  mu_run_test(test_count_single);
  mu_run_test(test_count_multiple);
  mu_run_test(test_count_none);
  return 0;
}

int main(int argc, char **argv) {
  printf("%s----------------------------\nRunning Data Processor Tests\n----------------------------\n%s", KCYN, KNRM);
  char* result = all_tests();
  if (0 != result) {
    printf("%sFailed Test:%s %s\n", KRED, KNRM, result);
  }
  printf("Tests Run: %s%d / %d%s\n", (tests_run == NUM_TESTS) ? KGRN : KRED, tests_run, NUM_TESTS, KNRM);
  printf("Tests Passed: %s%d / %d%s\n", (tests_passed == NUM_TESTS) ? KGRN : KRED, tests_passed, NUM_TESTS, KNRM);

  printf("%s----------------------------%s\n", KCYN, KNRM);
  return result != 0;
}