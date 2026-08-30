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

// P0.08 for symbols layer LED
static const struct gpio_dt_spec symbols_layer_led = {
    .port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
    .pin = 8,
    .dt_flags = GPIO_ACTIVE_HIGH,
};

// P0.06 for media layer LED
static const struct gpio_dt_spec media_layer_led = {
    .port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
    .pin = 6,
    .dt_flags = GPIO_ACTIVE_HIGH,
};

static int init_symbols_gpio(void) {
  if (!gpio_is_ready_dt(&symbols_layer_led)) {
    return -ENODEV;
  }

  return gpio_pin_configure_dt(&symbols_layer_led, GPIO_OUTPUT_INACTIVE);
}

static int init_media_gpio(void) {
  if (!gpio_is_ready_dt(&media_layer_led)) {
    return -ENODEV;
  }

  return gpio_pin_configure_dt(&media_layer_led, GPIO_OUTPUT_INACTIVE);
}

static void gpio_high(const struct gpio_dt_spec *pin) {
  gpio_pin_set_dt(pin, 1);
}

static void gpio_low(const struct gpio_dt_spec *pin) {
  gpio_pin_set_dt(pin, 0);
}

static int layer_gpio_handler(struct zmk_layer_state_changed const *event) {
  if (event->layer == 1) {
    if (event->state) {
      gpio_high(&symbols_layer_led);
    } else {
      gpio_low(&symbols_layer_led);
    }
  } else if (event->layer == 2) {
    if (event->state) {
      gpio_high(&media_layer_led);
    } else {
      gpio_low(&media_layer_led);
    }
  }
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

SYS_INIT(init_symbols_gpio, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
SYS_INIT(init_media_gpio, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
ZMK_LISTENER(led_toggle_on_layer, layer_gpio_listener);
ZMK_SUBSCRIPTION(led_toggle_on_layer, zmk_layer_state_changed);
