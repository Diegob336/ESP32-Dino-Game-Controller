#include "angle_detection.h"


void angle_filter_init( MPU6050_Angles_t *MPU6050_Angles){

}


void recursive_avg_filter( MPU6050_Angles_t *MPU6050_Angles){

}


void get_angle(MPU6050_data_t sensor_data, MPU6050_Angles_t *angles){
	
	float accel_x = sensor_data.accel_x;
	float accel_y = sensor_data.accel_y;
	float accel_z = sensor_data.accel_z;
	
	angles->roll= atan2(accel_y, accel_z) * (180/M_PI);
	angles->pitch = atan2(-accel_x, sqrt(accel_y * accel_y + accel_z * accel_z)) * (180 / M_PI);


	
}

