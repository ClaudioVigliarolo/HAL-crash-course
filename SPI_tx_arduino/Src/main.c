#include "main.h"
#include "string.h"

void Error_handler(void);
void Button_init(void);
void SPI2_Init(void);
char *user_data = "congrats! Spi is working";


SPI_HandleTypeDef hspi2;


int main()
{
	//hal init
	HAL_Init();

	//init the spi peripheral
	SPI2_Init();

	//init the button
	Button_init();

	//let's send some data

	uint8_t len = strlen(user_data);
	while(1)
	{
		while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));
		HAL_Delay(200);
		HAL_SPI_Transmit(&hspi2,  &len, 1 , HAL_MAX_DELAY);
		HAL_SPI_Transmit(&hspi2, (uint8_t*) user_data, len , HAL_MAX_DELAY);
	}

	return 0;
}


void Error_handler(void)
{
	while(1);
}


 void SPI2_Init(void)
{
	  hspi2.Instance = SPI2;
	  hspi2.Init.Mode = SPI_MODE_MASTER;
	  hspi2.Init.Direction = SPI_DIRECTION_1LINE;
	  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
	  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	  hspi2.Init.NSS = SPI_NSS_SOFT;
	  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	  if (HAL_SPI_Init(&hspi2) != HAL_OK)
	  {
		  Error_handler();
	  }
}

void Button_init(void)
{
	GPIO_InitTypeDef buttongpio;

	 __HAL_RCC_GPIOC_CLK_ENABLE();

	buttongpio.Pin = GPIO_PIN_13;
	buttongpio.Mode = GPIO_MODE_EVT_FALLING;
	buttongpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC,&buttongpio);

}



