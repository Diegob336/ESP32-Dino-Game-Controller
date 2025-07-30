idf_component_register(SRCS "src/mpu6050_driver.c"
                       INCLUDE_DIRS "."
					   REQUIRES	esp_driver_i2c)
