#include "stm32f4xx.h"
#include <stdio.h>

void delay_ms(uint32_t ms) {
    SysTick->LOAD = 16000 - 1;  // 1ms delay assuming 16MHz system clock
    SysTick->VAL = 0;
    SysTick->CTRL = 5;  // Enable SysTick, use processor clock

    for (uint32_t i = 0; i < ms; i++) {
        while (!(SysTick->CTRL & (1 << 16)));  // Wait for COUNTFLAG
    }

    SysTick->CTRL = 0;  // Disable SysTick
}

void ADC1_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;   // Enable ADC1 clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;  // Enable GPIOA clock

    GPIOA->MODER |= (3 << 0);  // PA0 as analog

    ADC1->CR2 |= ADC_CR2_ADON;  // Enable ADC
    ADC1->SQR3 = 0;             // First conversion on channel 0 (PA0)
}

uint16_t ADC1_Read(void) {
    ADC1->CR2 |= ADC_CR2_SWSTART;               // Start conversion
    while (!(ADC1->SR & ADC_SR_EOC));           // Wait for conversion complete
    return ADC1->DR;                             // Read data
}

void UART3_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_USART3EN;       // USART3 clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;        // GPIOD clock

    GPIOD->MODER |= (2 << (2 * 8));  // PD8 = AF mode
    GPIOD->AFR[1] |= (7 << ((8 - 8) * 4));  // AF7 (USART3_TX) for PD8

    USART3->BRR = 0x0683;     // Baud rate 9600 @ 16MHz
    USART3->CR1 |= USART_CR1_TE;    // Transmit enable
    USART3->CR1 |= USART_CR1_UE;    // USART enable
}

void UART3_SendChar(char c) {
    while (!(USART3->SR & USART_SR_TXE));
    USART3->DR = c;
}

void UART3_SendString(const char* str) {
    while (*str) {
        UART3_SendChar(*str++);
    }
}

int main(void) {
    char buffer[20];

    UART3_Init();
    ADC1_Init();

    while (1) {
        uint16_t mq2 = ADC1_Read();                   // Read analog value
        sprintf(buffer, "%d\n", mq2);                 // Convert to string with newline
        UART3_SendString(buffer);                     // Send to ESP8266
        delay_ms(2000);                               // Delay 2 seconds
    }
}
