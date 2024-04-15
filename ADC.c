#include "stm32f1xx.h"
uint32_t adc_data;
int main()
{
	/*Enable clock access to GPIOA*/
	//enable clock access to GPIOA
	RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
	/*Set PA0 to analog Mode*/
	GPIOA->CRL&=~GPIO_CRL_CNF0;
	GPIOA->CRL&=~GPIO_CRL_MODE0;

	/*Enable clock accrss to ADC1*/
	RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;

	/*Set the trigger to be software mode*/
	ADC1->CR2 |= (7UL << ADC_CR2_EXTSEL_Pos);
	/*Power up the adc*/
	ADC1->CR2|=ADC_CR2_ADON;
	/*Launch the ADC*/
	ADC1->CR2|=ADC_CR2_ADON;
	while(1)
	{
		/*Relaunch the ADC*/
		ADC1->CR2|=ADC_CR2_ADON;
		/*Launch the ADC conversion*/
		ADC1->CR2|=ADC_CR2_SWSTART;
		/*wait for EOC*/
		while(!(ADC1->SR &ADC_SR_EOC));
		adc_data=ADC1->DR;
	}
}
