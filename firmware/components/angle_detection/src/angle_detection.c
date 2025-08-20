#include "angle_detection.h"

extern volatile float q0, q1, q2, q3;

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

void madgwick_angle_init(Madgwick_Config_t *config, float sample_freq, float beta_gain){
	config->beta_gain = beta_gain;
	config->sample_frequency = sample_freq;
}
void get_angle_madgwick(MPU6050_data_t *sensor_data,  Filtered_angles_t *filtered_angles){
	float accel_x = sensor_data->accel_x;
	float accel_y = sensor_data->accel_y;
	float accel_z = sensor_data->accel_z;

	float gyro_x = sensor_data->gyro_x * (M_PI / 180);
	float gyro_y = sensor_data->gyro_y * (M_PI / 180);
	float gyro_z = sensor_data->gyro_z * (M_PI / 180);
	
	MadgwickAHRSupdateIMU(gyro_x, gyro_y, gyro_z, accel_x, accel_y, accel_z);

	filtered_angles->filtered_roll = atan2f(2.0f * (q0*q1 + q2*q3),
		1.0f - 2.0f * (q1*q1 + q2*q2)) * (180.0f / M_PI);
	filtered_angles->filtered_pitch = asinf(2.0f * (q0*q2 - q3*q1)) * (180.0f / M_PI);
	filtered_angles->filtered_yaw = atan2f(2.0f * (q0*q3 + q1*q2),
		1.0f - 2.0f * (q2*q2 + q3*q3)) * (180.0f / M_PI);
}


dino_cmd_t detect_gesture(MPU6050_data_t *sensor_data, Filtered_angles_t *filtered_angles, Gesture_detector_t *gesture_detector){

	gesture_detector->cmd = NO_COMMAND; // reset command value

	float delta_y = sensor_data->gyro_y - gesture_detector->prev_gyro_y;

	if((delta_y < -gesture_detector->jump_threshold) && filtered_angles->filtered_pitch < 0){
		gesture_detector->cmd = JUMP;
		ESP_LOGI("DEBUG", "Current: %f, Previous: %f, Delta: %f", 
	   sensor_data->gyro_y, gesture_detector->prev_gyro_y, delta_y);
	}
	else if (delta_y > gesture_detector->duck_threshold && filtered_angles->filtered_pitch > 0){
		gesture_detector->cmd = DUCK;
		ESP_LOGI("DEBUG", "Current: %f, Previous: %f, Delta: %f", 
	   sensor_data->gyro_y, gesture_detector->prev_gyro_y, delta_y);

	}
	gesture_detector->prev_gyro_y = sensor_data->gyro_y;
	
	return gesture_detector->cmd;
}

