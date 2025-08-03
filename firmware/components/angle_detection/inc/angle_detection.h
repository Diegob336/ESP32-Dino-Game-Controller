#ifndef ANGLE_DETECTION_H
#define ANGLE_DETECTION_H

#include "mpu6050_driver.h"
#include <math.h> 

#define M_PI 3.1415927f

typedef struct {
	float roll;
	float pitch;
	float yaw;
}MPU6050_Angles_t;

void angle_filter_init( MPU6050_Angles_t *angles);
void recursive_avg_filter( MPU6050_Angles_t *angles);
void get_angle(MPU6050_data_t sensor_data, MPU6050_Angles_t *angles);


#endif
