# Data Processor [![Build Status](http://img.shields.io/travis/smallstoneapps/data-processor.svg?style=flat-square)](https://travis-ci.org/smallstoneapps/data-processor/)&nbsp;![Version 2.1.0](http://img.shields.io/badge/version-2.1.0-orange.svg?style=flat-square)&nbsp;[![MIT License](http://img.shields.io/badge/license-MIT-lightgray.svg?style=flat-square)](./LICENSE)


Pebble library to extract strings, ints and booleans from a long string of data.

## Usage

````c
// This is not a complete example, but should demonstrate
// the basic usage of Data Processor.

static void parse_data(char* data) {
  ProcessingState* state = data_processor_create(data, '|');
  uint8_t num_strings = data_processor_count();
  char** strings = malloc(sizeof(char*) * num_strings);
  for (uint8_t n = 0; n < num_strings; n += 1) {
    strings[n] = data_processor_get_string(state);
  }
}
````

## Tests

Unit tests for Data Processor exist in the `tests` folder.

To run the tests:

```sh
make test
```

## Function Documentation

Initialise the global Data Processor state object with a string of data and a
delimiter character.

````c
void data_processor_init(char* data, char delim);
````

Create and return a new Data Processor state object with a string of data and a
delimiter character.

````c
ProcessingState* data_processor_create(char* data, char delim);
````

Destroy a Data Processor state object.

````c
void data_processor_destroy(ProcessingState* state);
````

Destroys the global Data Processor state object.

````c
void data_processor_deinit();
````

Get the global Data Processor state object, used for passing to the functions below.

````c
ProcessingState* data_processor_get_global(void);
````

Get the count of the remaining subelements for a Data Processor state object.

````c
uint8_t data_processor_count(ProcessingState* state);
````

Get the next element as a string for a Data Processor state object.

````c
char* data_processor_get_string(ProcessingState* state);
````

Get the next element as a bool for a Data Processor state object.

````c
bool data_processor_get_bool(ProcessingState* state);
````

Get the next element as an int for a Data Processor state object.

````c
int data_processor_get_int(ProcessingState* state);
````
