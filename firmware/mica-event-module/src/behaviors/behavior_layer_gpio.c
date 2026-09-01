#define DT_DRV_COMPAT zmk_behavior_layer_gpio

#include <drivers/behavior.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include <zmk/behavior.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#define MICA_SYMBOLS_LED 0
#define MICA_MEDIA_LED 1

static const struct gpio_dt_spec symbols_layer_led = {
    .port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
    .pin = 8,
    .dt_flags = GPIO_ACTIVE_HIGH,
};
static const struct gpio_dt_spec media_layer_led = {
    .port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
    .pin = 6,
    .dt_flags = GPIO_ACTIVE_HIGH,
};

static int gpio_led_init(const struct device *dev) {
  gpio_pin_configure_dt(&symbols_layer_led, GPIO_OUTPUT_INACTIVE);
  gpio_pin_configure_dt(&media_layer_led, GPIO_OUTPUT_INACTIVE);
  return 0;
}

static const struct gpio_dt_spec *led_for(uint32_t led_id) {
  switch (led_id) {
  case MICA_SYMBOLS_LED:
    return &symbols_layer_led;
    break;
  case MICA_MEDIA_LED:
    return &media_layer_led;
    break;
  default:
    return &symbols_layer_led;
  }
}

static int
on_gpio_led_binding_pressed(struct zmk_behavior_binding *binding,
                            struct zmk_behavior_binding_event event) {
  gpio_pin_set_dt(led_for(binding->param1), 1);
  return ZMK_BEHAVIOR_OPAQUE;
}

static int
on_gpio_led_binding_released(struct zmk_behavior_binding *binding,
                             struct zmk_behavior_binding_event event) {
  gpio_pin_set_dt(led_for(binding->param1), 0);
  return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api gpio_led_driver_api = {
    .binding_pressed = on_gpio_led_binding_pressed,
    .binding_released = on_gpio_led_binding_released,
    .locality = BEHAVIOR_LOCALITY_GLOBAL,
};

BEHAVIOR_DT_INST_DEFINE(0, gpio_led_init, NULL, NULL, NULL, POST_KERNEL,
                        CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
                        &gpio_led_driver_api);
