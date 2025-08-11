#ifndef ANGLE_DETECTION_H
#define ANGLE_DETECTION_H

#include "mpu6050_driver.h"
#include "MadgwickAHRS.h"
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
	float filtered_yaw;
	float alpha;
}Filtered_angles_t;

typedef struct {
    float sample_frequency;
    float beta_gain;
}Madgwick_Config_t;

typedef struct {
	float prev_gyro_y;
	float prev_gyro_x;
	float jump_threshold;
	uint8_t jump_detected;

}Jump_detector_t;

void angle_filter_init( Filtered_angles_t *filtered_angles);
void recursive_avg_filter( MPU6050_Angles_t *angles, Filtered_angles_t *filtered_angles);
void get_angle(MPU6050_data_t *sensor_data, MPU6050_Angles_t *angles);

void madgwick_angle_init(Madgwick_Config_t *config, float sample_freq, float beta_gain);
void get_angle_madgwick(MPU6050_data_t *sensor_data, Filtered_angles_t *filtered_angles);

uint8_t detect_jump(MPU6050_data_t *sensor_data, Jump_detector_t *jump_detector);

#endif
