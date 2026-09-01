#include <drivers/behavior.h>
#include <drivers/input_processor.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zmk/behavior.h>
#include <zmk/event_manager.h>
#include <zmk/events/keycode_state_changed.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/events/position_state_changed.h>
#include <zmk/hid.h>
#include <zmk/keymap.h>
#include <zmk/matrix.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

static int layer_gpio_handler(struct zmk_layer_state_changed const *event) {
  uint32_t led_id;
  if (event->layer == 1)
    led_id = 0; // SYMBOLS_LED in layer_gpio.c
  else if (event->layer == 2)
    led_id = 1; // MEDIA_LED in layer_gpio.c
  else
    return ZMK_EV_EVENT_BUBBLE;

  struct zmk_behavior_binding binding = {
      .behavior_dev = "gpiled",
      .param1 = led_id,
  };

  struct zmk_behavior_binding_event ev = {
      .position = 0,
      .timestamp = k_uptime_get(),
  };

  zmk_behavior_invoke_binding(&binding, ev, event->state);

  return ZMK_EV_EVENT_BUBBLE;
}

static int layer_gpio_listener(zmk_event_t const *event) {
  struct zmk_layer_state_changed const *const event_subclass =
      as_zmk_layer_state_changed(event);
  if (event_subclass != NULL) {
    return layer_gpio_handler(event_subclass);
  }
  return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(led_toggle_on_layer, layer_gpio_listener);
ZMK_SUBSCRIPTION(led_toggle_on_layer, zmk_layer_state_changed);
