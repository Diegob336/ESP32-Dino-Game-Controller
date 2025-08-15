#ifndef UART_COMM_H
#define UART_COMM_H

#include <stdint.h>
#include "driver/uart.h"
#include "esp_log.h"

#define UART_COMM_START_BYTE    0xAA
#define UART_COMM_END_BYTE      0x67

typedef enum {
	NO_COMMAND,
	JUMP,
	DUCK,
} dino_cmd_t;

void Uart_init();
void Uart_send_command(dino_cmd_t cmd);

#endif 
