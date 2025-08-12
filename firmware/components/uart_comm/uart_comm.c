#include "uart_comm.h"

uint8_t calculate_checksum(uint8_t *data, uint16_t length);

uart_port_t uart_port_num = UART_NUM_0;


void Uart_init(){

	uart_config_t uart_config = {
		.baud_rate = 115200,
		.data_bits = UART_DATA_8_BITS,
		.parity = UART_PARITY_DISABLE,
		.stop_bits = UART_STOP_BITS_1,
		.flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
	};

	ESP_ERROR_CHECK(uart_driver_install(uart_port_num, 2048, 2048, 0, NULL, 0));
	ESP_ERROR_CHECK(uart_param_config(uart_port_num, &uart_config));
	ESP_ERROR_CHECK(uart_set_pin(uart_port_num, 1, 3, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
}
void Uart_send_command(dino_cmd_t cmd){
	uint8_t packet[4];
	packet[0] = UART_COMM_START_BYTE;
	packet[1] = cmd;
	packet[2] = calculate_checksum((uint8_t *)&cmd, 1); 
	packet[3] = UART_COMM_END_BYTE;

	int ret = uart_write_bytes(uart_port_num, packet, sizeof(packet));
	if ( ret == -1) {
		ESP_LOGE("UART Error", "Error writing bytes to buffer");
	}else {
		ESP_LOGI("UART", "Succesfully sent %d bytes", ret);
	}
}


uint8_t calculate_checksum(uint8_t *data, uint16_t length) {
	uint8_t sum = 0;
	for (int i = 0; i < length; i++) {
		sum += *(data + i);
	}
	return sum;
}

