#include <pebble.h>
#include "../../include/data-processor.h"

static void init(void);
static void deinit(void);
static void window_load(Window *window);
static void window_unload(Window *window);

static Window *window;
static TextLayer *text_layer;

int main(void) {
  init();
  app_event_loop();
  deinit();
}

static void init(void) {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

static void window_load(Window *window) {
  data_processor_init("Sample|split|string|5", '|');
  char* message = data_processor_get_string(data_processor_get_global());

  text_layer = text_layer_create(GRect(0, 72, 144, 20));
  text_layer_set_text(text_layer, message);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}
