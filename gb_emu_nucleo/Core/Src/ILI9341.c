/*
 * adafruit_2-8in_tft.c
 *
 *  Created on: Sep 28, 2025
 *  Author: Zulaikha Zakiullah
 *
 *  Driver for Adafruit 2.8" TFT touchscreen (ILI9341)
 */

#include <ILI9341.h>

HAL_StatusTypeDef ILI9341_Init(void) {
  // Read and verify ID
  const id = 0;
  if (id != ILI9341_ID) {
    return HAL_ERROR;
  }

  ILI9341_CS_ACTIVE;
  ILI9341_WriteRegister8(ILI9341_SOFTRESET, 0);
  HAL_Delay(50);
  ILI9341_WriteRegister8(ILI9341_DISPLAYOFF, 0);


}

HAL_StatusTypeDef ILI9341_Reset(void) {
  ILI9341_CS_IDLE;
//  ILI9341_CD_DATA;
  ILI9341_WR_IDLE;
  ILI9341_RD_IDLE;

  // Reset pin is active low (connect to GND to reset)
  HAL_GPIO_WritePin(SCREEN_RST_GPIO_Port, SCREEN_RST_Pin, GPIO_PIN_RESET);
  HAL_Delay(500);
  HAL_GPIO_WritePin(SCREEN_RST_GPIO_Port, SCREEN_RST_Pin, GPIO_PIN_SET);

  // Data transfer sync
  ILI9341_CS_ACTIVE;
  ILI9341_CD_DATA;
  ILI9341_Write8(0x00);
  for (uint8_t i = 0; i < 3; i++) {
    ILI9341_WR_STROBE;
  }
  ILI9341_CS_IDLE;
}
