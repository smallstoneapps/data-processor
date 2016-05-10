#include <pebble.h>
#include "data-processor.h"


struct ProcessingState {
  char* data_start;
  char* data_pos;
  char data_delim;
};


static ProcessingState* global = NULL;


void data_processor_init(char* data, char delim) {
  data_processor_deinit();
  global = data_processor_create(data, delim);
}

ProcessingState* data_processor_create(char* data, char delim) {
  ProcessingState* state = malloc(sizeof(ProcessingState));
  state->data_start = data;
  state->data_pos = data;
  state->data_delim = delim;
  return state;
}

void data_processor_destroy(ProcessingState* state) {
  if (NULL == state) {
    return;
  }
  free(state);
}

void data_processor_deinit() {
  data_processor_destroy(global);
  global = NULL;
}

ProcessingState* data_processor_get_global(void) {
  return global;
}

uint8_t data_processor_count(ProcessingState* state) {
  if (NULL == state) {
    return 0;
  }
  if (strlen(state->data_start) == 0) {
    return 0;
  }
  char* pos = state->data_start;
  uint8_t count = 0;
  while (*pos != '\0') {
    if (*pos == state->data_delim) {
      count += 1;
    }
    pos++;
  }
  return ++count;
}

char* data_processor_get_string(ProcessingState* state) {
  if (NULL == state) {
    return NULL;
  }
  char* data_block_start = state->data_pos;
  int str_len = 0;
  while (*state->data_pos != state->data_delim && *state->data_pos != '\0') {
    state->data_pos++;
    str_len += 1;
  }
  char* tmp = malloc(str_len + 1);
  strncpy(tmp, data_block_start, str_len + 1);
  tmp[str_len] = '\0';
  state->data_pos++;
  return tmp;
  return NULL;
}

bool data_processor_get_bool(ProcessingState* state) {
  if (NULL == state) {
    return false;
  }
  char bool_char =  *state->data_pos;
  state->data_pos++;
  state->data_pos++;
  return (bool_char == '1');
}

int data_processor_get_int(ProcessingState* state) {
  if (NULL == state) {
    return -1;
  }
  char* tmp_str = data_processor_get_string(state);
  int num = atoi(tmp_str);
  free(tmp_str);
  return num;
}
