#ifndef MPU6050_DRIVER_H
#define MPU6050_DRIVER_H

#include <stdint.h>
#include "driver/i2c_master.h"

#define MPU6050_ADDR                          0x68

#define MPU6050_WHO_AM_I_REG                  0x75

// self test registers
#define MPU6050_SELF_TEST_X_REG               0x0D
#define MPU6050_SELF_TEST_Y_REG               0x0E
#define MPU6050_SELF_TEST_Z_REG               0x0F

//config registers
#define MPU6050_SMPLRT_DIV_REG                0x19
#define MPU6050_CONFIG_REG                    0x1A
#define MPU6050_GYRO_CONFIG_REG               0x1B
#define MPU6050_ACCEL_CONFIG_REG              0x1C
#define MPU6050_FIFO_EN_REG                   0x23

// Interrupt registers
#define MPU6050_INT_PIN_CFG_REG               0x37
#define MPU6050_INT_ENABLE_REG                0x38
#define MPU6050_INT_STATUS_REG                0x3A

// Accel registers
#define MPU6050_ACCEL_XOUT_H_REG              0x3B
#define MPU6050_ACCEL_XOUT_L_REG              0x3C
#define MPU6050_ACCEL_YOUT_H_REG              0x3D
#define MPU6050_ACCEL_YOUT_L_REG              0x3E
#define MPU6050_ACCEL_ZOUT_H_REG              0x3F
#define MPU6050_ACCEL_ZOUT_L_REG              0x40

// Temp registers
#define MPU6050_TEMP_OUT_H_REG                0x41
#define MPU6050_TEMP_OUT_L_REG                0x42

//Gyro registers
#define MPU6050_GYRO_XOUT_H_REG               0x43
#define MPU6050_GYRO_XOUT_L_REG               0x44
#define MPU6050_GYRO_YOUT_H_REG               0x45
#define MPU6050_GYRO_YOUT_L_REG               0x46
#define MPU6050_GYRO_ZOUT_H_REG               0x47
#define MPU6050_GYRO_ZOUT_L_REG               0x48

// power managment register
#define MPU6050_PWR_MGMT_1_REG                0x6B


typedef struct {
	float accel_x;   // Acceleration in g
    float accel_y;
    float accel_z;

    float gyro_x;    // Angular velocity in deg/s
    float gyro_y;
    float gyro_z;

}MPU6050_data_t;

typedef struct {
	uint8_t smplrt_div;
	uint8_t config;
	uint8_t gyro_config;
	uint8_t accel_config;
	uint8_t fifo_en;
	float lsb_per_g;
	float lsb_per_deg;
} MPU6050_Config_t;

typedef struct {
 	MPU6050_data_t mpu_data;
	MPU6050_Config_t mpu_config;
 } MPU6050_Handle_t;

//config related macros
#define SMPLRT_DIV_DEFAULT                   0x07

#define DLPF_CFG_260Hz                        0
#define DLPF_CFG_184Hz                        1
#define DLPF_CFG_94Hz                         2
#define DLPF_CFG_44Hz                         3
#define DLPF_CFG_21Hz                         4
#define DLPF_CFG_10Hz                         5
#define DLPF_CFG_5Hz                          6

#define GYRO_FSR_250                          0
#define GYRO_FSR_500                          1
#define GYRO_FSR_1000                         2
#define GYRO_FSR_2000                         3

//General macros
#define WAKE_UP_VAL                           0

void writeToMPU6050(i2c_master_dev_handle_t *dev_handle, uint8_t addr, uint8_t val);
void MPU6050_Init(MPU6050_Handle_t *MPUHandle, i2c_master_dev_handle_t *dev_handle);
void MPU6050_Read_All_Sensor_Data(MPU6050_Handle_t *MPUHandle, i2c_master_dev_handle_t *dev_handle);
 


#endif
