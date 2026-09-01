cmake_minimum_required(VERSION 3.13.1)

zephyr_library()
if(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
    zephyr_library_sources(src/layer_gpio.c)
endif()
zephyr_library_sources(src/behaviors/behavior_layer_gpio.c)
zephyr_include_directories(${APPLICATION_SOURCE_DIR}/include)
