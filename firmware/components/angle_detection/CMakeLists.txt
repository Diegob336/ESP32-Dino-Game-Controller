idf_component_register(SRCS "src/angle_detection.c"
		       INCLUDE_DIRS "inc"
		       PRIV_REQUIRES mpu6050_driver
			PRIV_REQUIRES madgwick
			PRIV_REQUIRES uart_comm
			)
