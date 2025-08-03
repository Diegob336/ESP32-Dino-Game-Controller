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

typedef struct {
	float filtered_roll;
	float filtered_pitch;
	float alpha;
}Filtered_angles_t;

void angle_filter_init( Filtered_angles_t *filtered_angles);
void recursive_avg_filter( MPU6050_Angles_t *angles, Filtered_angles_t *filtered_angles);
void get_angle(MPU6050_data_t *sensor_data, MPU6050_Angles_t *angles);


#endif
