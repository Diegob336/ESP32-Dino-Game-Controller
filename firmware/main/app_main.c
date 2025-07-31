#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "mpu6050_driver.h"



void app_main(void) {

	i2c_master_bus_handle_t bus_handle; 

	i2c_master_bus_config_t bus_config = {
		.i2c_port = I2C_NUM_0,
		.sda_io_num = 21,
		.scl_io_num = 22,
		.clk_source = I2C_CLK_SRC_DEFAULT,
		.glitch_ignore_cnt = 7,
		.flags.enable_internal_pullup = true,
	};

	ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &bus_handle));


	i2c_master_dev_handle_t dev_handle;

	i2c_device_config_t dev_config = {
		.dev_addr_length = I2C_ADDR_BIT_LEN_7,
		.device_address = MPU6050_ADDR,
		.scl_speed_hz = 400000,
	};


	ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_config, &dev_handle));


	MPU6050_Handle_t MPUHandle = {
		.mpu_config = {
			.smplrt_div = SMPLRT_DIV_DEFAULT,
			.config = DLPF_CFG_44Hz,
			.gyro_config = GYRO_FSR_250,
			.accel_config = ACCEL_FSR_2G,
		},
		.accel_x_offset = 0.08,
		.accel_y_offset = (-0.01),
		.accel_z_offset = (0.92 - 1.0),
		.gyro_x_offset = 0.15,
		.gyro_y_offset = (-1.01),
		.gyro_z_offset = 0.39,

	};

	MPU6050_Init(&MPUHandle, dev_handle);

	while(1) {
		MPU6050_Read_All_Sensor_Data( &MPUHandle, dev_handle);
		ESP_LOGI("Sensor Readings", "g_force x: %2f, y: %2f, z: %2f", MPUHandle.mpu_data.accel_x, MPUHandle.mpu_data.accel_y, MPUHandle.mpu_data.accel_z);
		ESP_LOGI("Sensor Readings", "gyro x: %2f, y: %2f, z: %2f", MPUHandle.mpu_data.gyro_x, MPUHandle.mpu_data.gyro_y, MPUHandle.mpu_data.gyro_z);	
		vTaskDelay(pdMS_TO_TICKS(400));
	}

}
