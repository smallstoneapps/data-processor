#pragma once


#include <pebble.h>


typedef struct ProcessingState ProcessingState;


void data_processor_init(char* data, char delim);
ProcessingState* data_processor_create(char* data, char delim);
void data_processor_destroy(ProcessingState* state);
void data_processor_deinit();
ProcessingState* data_processor_get_global(void);
uint8_t data_processor_count(ProcessingState* state);
char* data_processor_get_string(ProcessingState* state);
bool data_processor_get_bool(ProcessingState* state);
int data_processor_get_int(ProcessingState* state);
