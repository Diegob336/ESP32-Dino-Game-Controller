cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(esp32_dino_controller)

set(EXTRA_COMPONENT_DIRS components/mpu6050_driver
			components/angle_detection
			components/madgwick
			components/uart_comm
)
