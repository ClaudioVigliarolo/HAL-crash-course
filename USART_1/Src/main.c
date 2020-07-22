#include "main.h"
#include "string.h"

void USART2_init(void);
void Error_handler(void);

char *user_data = "Hi there!";

UART_HandleTypeDef huart2;
int main()
{
	//hal init
	HAL_Init();

	//init the usart
	USART2_init();

	//let's send some data

	uint16_t len = strlen(user_data);


	HAL_UART_Transmit(&huart2, (uint8_t*) user_data, len, HAL_MAX_DELAY);

	while(1);

	return 0;
}

void USART2_init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;

	if(HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_handler();
	}


}


void Error_handler(void)
{
	while(1);
}
