#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "mpu6050_driver.h"
#include "angle_detection.h"
#include "uart_comm.h"

void readDataTask(void *parameter){
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

	MPU6050_Angles_t angles;

	Filtered_angles_t filtered_angles;

	angle_filter_init(&filtered_angles);

	MPU6050_Init(&MPUHandle, dev_handle);

	Gesture_detector_t gesture_detector = {
		.prev_gyro_y = 0.0,
		.jump_threshold = 50.0,
		.duck_threshold = 50.0
	};

	Uart_init();


	uint64_t last_jump_time = 0;
	uint64_t curr_time;

	while(1) {

		MPU6050_Read_All_Sensor_Data( &MPUHandle, dev_handle);
			
		get_angle_madgwick(&MPUHandle.mpu_data, &filtered_angles);

		curr_time = esp_timer_get_time();
		switch (detect_gesture(&MPUHandle.mpu_data, &filtered_angles, &gesture_detector)){
			case JUMP:
				// if time differnce is greater than .5 seconds
				if ((curr_time - last_jump_time) > 500000){
					ESP_LOGI("GESTURE", "JUMP detected");
					Uart_send_command(JUMP);
					last_jump_time = curr_time;
				}
				break;
			case DUCK:
				if ((curr_time - last_jump_time) > 500000){
					ESP_LOGI("GESTURE", "DUCK detected");
					Uart_send_command(DUCK);
					last_jump_time = curr_time;
				}
				break;
			default:
				break;

		}


		ESP_LOGI("Angle Readings", "Roll: %2f, Pitch: %2f, Yaw: %2f", filtered_angles.filtered_roll, filtered_angles.filtered_pitch, filtered_angles.filtered_yaw);
		vTaskDelay(pdMS_TO_TICKS(10));
	}
	

}

void app_main(void) {
	
	xTaskCreatePinnedToCore(&readDataTask, "read sensor data", 4096, NULL, 0, NULL, 1);


}
