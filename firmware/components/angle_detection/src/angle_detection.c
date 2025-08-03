#include "angle_detection.h"


void angle_filter_init(Filtered_angles_t *filtered_angles){
	filtered_angles->filtered_roll = 0.0;
	filtered_angles->filtered_pitch = 0.0;
	filtered_angles->alpha = 0.3;
}


void recursive_avg_filter( MPU6050_Angles_t *MPU6050_Angles, Filtered_angles_t *filtered_angles){

	float new_roll = MPU6050_Angles->roll;
	float new_pitch = MPU6050_Angles->pitch;

	filtered_angles->filtered_roll = filtered_angles->alpha * new_roll + (1 - filtered_angles->alpha) * filtered_angles->filtered_roll;
	filtered_angles->filtered_pitch = filtered_angles->alpha * new_pitch + (1 - filtered_angles->alpha) *filtered_angles->filtered_pitch;
}


void get_angle(MPU6050_data_t *sensor_data, MPU6050_Angles_t *angles){
	
	float accel_x = sensor_data->accel_x;
	float accel_y = sensor_data->accel_y;
	float accel_z = sensor_data->accel_z;
	
	angles->roll= atan2(accel_y, accel_z) * (180 / M_PI);
	angles->pitch = atan2(-accel_x, sqrt(accel_y * accel_y + accel_z * accel_z)) * (180 / M_PI);


	
}

