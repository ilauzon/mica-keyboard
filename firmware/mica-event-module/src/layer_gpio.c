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

// P0.06 for layer 1 LED
static const struct gpio_dt_spec layer_led = {
    .port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
    .pin = 6,
    .dt_flags = GPIO_ACTIVE_HIGH,
};

static int init_gpio(void) {
  if (!gpio_is_ready_dt(&layer_led)) {
    return -ENODEV;
  }

  return gpio_pin_configure_dt(&layer_led, GPIO_OUTPUT_INACTIVE);
}

static void gpio_high(void) { gpio_pin_set_dt(&layer_led, 1); }

static void gpio_low(void) { gpio_pin_set_dt(&layer_led, 0); }

static int layer_gpio_handler(struct zmk_layer_state_changed const *event) {
  if (event->layer == 1) {
    if (event->state) {
      gpio_high();
    } else {
      gpio_low();
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

SYS_INIT(init_gpio, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
ZMK_LISTENER(led_toggle_on_layer, layer_gpio_listener);
ZMK_SUBSCRIPTION(led_toggle_on_layer, zmk_layer_state_changed);
