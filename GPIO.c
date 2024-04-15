#include "GPIO.h"

int main()
	{
//		int value;
		GPIO_Init(GPIOA, PIN_2, OUT_PUT);
		GPIO_Init(GPIOA, PIN_8, OUT_PUT);
	
		while(1)
		{
			//value = gpio_get_value(GPIOA, 2);
			gpio_set_value(GPIOA, 2, 1);
			gpio_set_value(GPIOA, 8, 1);
//			if(value==1)
//				{
//					gpio_set_value(GPIOA, 1, 1);
//				}
//			else
//				{
//					gpio_set_value(GPIOA, 1, 0);
//				}
		}
	}

void GPIO_Init(GPIO_TypeDef *GPIOx, int PIN, int mode)
	{
		GPIO_Set_Clk(GPIOx);
		GPIO_Set_Mode(GPIOx, PIN, mode);
	}
	
void gpio_set_value(GPIO_TypeDef *GPIOx, int PIN, int value)
	{
		if(value == 1)
			{
				GPIOx->ODR |= (1<<PIN);
			}
		else
			{
				GPIOx->ODR &= ~(1<<PIN);	
			}
	}

int gpio_get_value(GPIO_TypeDef *GPIOx, int PIN)
	{
		int bitstatus;
		GPIOx->ODR |= (1<<PIN);
		if ((GPIOx->IDR & (1<<PIN))==0)
		{
			bitstatus = 1;
		}
		else
		{
			bitstatus = 0;
		}
		return bitstatus;
	}

void GPIO_Set_Clk(GPIO_TypeDef *GPIOx)
	{
		if(GPIOx == GPIOA)
			{
				RCC->APB2ENR |= 1<<2;                  // Enable Clock cho Port A
			}
		else if(GPIOx == GPIOB)
			{
				RCC->APB2ENR |= 1<<3;								   // Enable Clock cho Port B
			}
		else if(GPIOx == GPIOC)
			{
				RCC->APB2ENR |= 1<<4;								   // Enable Clock cho Port C
			}
	}

void GPIO_Set_Mode(GPIO_TypeDef *GPIOx, int PIN, int mode)
	{
		if(mode==1)
			{
				if(PIN == PIN_0 | PIN == PIN_1 | PIN == PIN_2 | PIN == PIN_3 | PIN == PIN_4 | PIN == PIN_5 | PIN == PIN_6 | PIN == PIN_7)
				{
					GPIOx->CRL &= 0x00;
					GPIOx->CRL |= 1<<PIN;			  
					GPIOx->CRL |= 1<<(PIN + 1);
				}
				else if(PIN == PIN_8 | PIN == PIN_9 | PIN == PIN_10 | PIN == PIN_11 | PIN == PIN_12 | PIN == PIN_13 | PIN == PIN_14 | PIN == PIN_15)
				{
					GPIOx->CRH &= 0x00;				
					GPIOx->CRH |= 1<<(PIN-1);			   
					GPIOx->CRH |= 1<<PIN;
				}
			}
		else if(mode==0)
			{
				if(PIN == PIN_0 | PIN == PIN_1 | PIN == PIN_2 | PIN == PIN_3 | PIN == PIN_4 | PIN == PIN_5 | PIN == PIN_6 | PIN == PIN_7)
				{
					GPIOx->CRL &= 0x00;              
					GPIOx->CRH &= ~(1<<PIN);
					GPIOx->CRL &= ~(1<<(PIN+2));
					GPIOx->CRH &= ~(1<<(PIN+1));			   
					GPIOx->CRL |= (1<<(PIN+3));
				}
				else if(PIN == PIN_8 | PIN == PIN_9 | PIN == PIN_10 | PIN == PIN_11 | PIN == PIN_12 | PIN == PIN_13 | PIN == PIN_14 | PIN == PIN_15)
				{
					GPIOx->CRH &= 0x00;             
					GPIOx->CRH &= ~(1<<(PIN-1));			   
					GPIOx->CRH &= ~(1<<PIN);
					GPIOx->CRL &= ~(1<<(PIN+2));
					GPIOx->CRL |= (1<<(PIN+3));
				}
			}
	}
void delay_ms(int n)
	{
		n = n*10000;
		while(n!=0)
		{
			n--;
		}
	}


