cmake_minimum_required(VERSION 3.13.1)

zephyr_library()
zephyr_library_sources(src/layer_gpio.c)
zephyr_include_directories(${APPLICATION_SOURCE_DIR}/include)
