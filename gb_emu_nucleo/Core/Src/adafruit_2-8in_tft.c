/*
 * adafruit_2-8in_tft.c
 *
 *  Created on: Sep 28, 2025
 *  Author: Zulaikha Zakiullah
 *
 *  Driver for Adafruit 2.8" TFT touchscreen
 */

#include "adafruit_2-8in_tft.h"

HAL_StatusTypeDef Adafruit28TFT_Init(void) {
  // Read and verify ID
  GPIO_PinState state = HAL_GPIO_ReadPin(SCREEN_RD_GPIO_Port, SCREEN_RD_Pin);
}
