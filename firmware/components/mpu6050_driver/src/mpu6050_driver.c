#include "inc/mpu6050_driver.h"

void writeToMPU6050(i2c_master_dev_handle_t *dev_handle, uint8_t addr, uint8_t val){
	
	uint8_t data[] = { addr, val };
	ESP_ERROR_CHECK(i2c_master_transmit(*dev_handle, data, sizeof(data), -1));
}

void MPU6050_Init(MPU6050_Handle_t *MPUHandle, i2c_master_dev_handle_t *dev_handle ){

	uint8_t smplrt_div = MPUHandle->mpu_config.smplrt_div;
	uint8_t config = MPUHandle->mpu_config.config;
	uint8_t gyro_config = MPUHandle->mpu_config.gyro_config;
	uint8_t accel_config = MPUHandle->mpu_config.accel_config;

	// wake up the sesnor
	writeToMPU6050(dev_handle, MPU6050_PWR_MGMT_1_REG, WAKE_UP_VAL);

	// configure the sensor
	writeToMPU6050(dev_handle, MPU6050_SMPLRT_DIV_REG, smplrt_div);
	 
	writeToMPU6050(dev_handle, MPU6050_CONFIG_REG, config);

	writeToMPU6050(dev_handle, MPU6050_GYRO_CONFIG_REG, gyro_config);

	writeToMPU6050(dev_handle, MPU6050_ACCEL_CONFIG_REG, accel_config);

	uint8_t gyro_fsr = (gyro_config >> 3) & 0x03;
	uint8_t accel_fsr = (accel_config >> 3) & 0x03;
	
	switch (gyro_fsr) {
		case 0: 
			MPUHandle->mpu_config.lsb_per_deg = 131.0;
			break;
		case 1:
			MPUHandle->mpu_config.lsb_per_deg = 65.5;
			break;
	case 2:
			MPUHandle->mpu_config.lsb_per_deg = 32.8;
			break;
		case 3:
			MPUHandle->mpu_config.lsb_per_deg = 16.4;
			break;
		default:
			break;
	}

	switch (accel_fsr) {
		case 0: 
			MPUHandle->mpu_config.lsb_per_g = 16384.0;
			break;
		case 1:
			MPUHandle->mpu_config.lsb_per_g = 8192.0;
			break;
		case 2:
			MPUHandle->mpu_config.lsb_per_g = 4096.0;
			break;
		case 3:
			MPUHandle->mpu_config.lsb_per_g = 2048.0;
			break;
		default:
			break;
}

}

void MPU6050_Read_All_Sensor_Data(MPU6050_Handle_t *MPUHandle, i2c_master_dev_handle_t *dev_handle){
	
	uint8_t sensor_data[14];

	uint8_t reg_addr = MPU6050_ACCEL_XOUT_H_REG;

	float lsb_per_deg = MPUHandle->mpu_config.lsb_per_deg;
	float lsb_per_g = MPUHandle->mpu_config.lsb_per_g;
	ESP_ERROR_CHECK(i2c_master_transmit_receive(*dev_handle, &reg_addr, 1, sensor_data, 14, -1));

	// Parse the raw values
	int16_t raw_accel_x = (sensor_data[0] << 8) | sensor_data[1];
	int16_t raw_accel_y = (sensor_data[2] << 8) | sensor_data[3];
	int16_t raw_accel_z = (sensor_data[4] << 8) | sensor_data[5];

	int16_t raw_gyro_x = (sensor_data[8]  << 8) | sensor_data[9];
	int16_t raw_gyro_y = (sensor_data[10] << 8) | sensor_data[11];
	int16_t raw_gyro_z = (sensor_data[12] << 8) | sensor_data[13];

	MPUHandle->mpu_data.accel_x = (float)raw_accel_x / lsb_per_g;
	MPUHandle->mpu_data.accel_y  = (float)raw_accel_y / lsb_per_g;
	MPUHandle->mpu_data.accel_z  = (float)raw_accel_z / lsb_per_g;

	MPUHandle->mpu_data.gyro_x = (float)raw_gyro_x / lsb_per_deg;
	MPUHandle->mpu_data.gyro_y = (float)raw_gyro_y / lsb_per_deg;
	MPUHandle->mpu_data.gyro_z = (float)raw_gyro_z / lsb_per_deg;


}
