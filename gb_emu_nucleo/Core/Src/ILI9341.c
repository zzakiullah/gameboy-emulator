/*
 * ILI9341.c
 *
 *  Created on: Sep 28, 2025
 *  Author: Zulaikha Zakiullah
 *
 *  Driver for Adafruit 2.8" TFT touchscreen (ILI9341)
 */

#include <ILI9341.h>

HAL_StatusTypeDef ILI9341_Write8(uint8_t value) {}

HAL_StatusTypeDef ILI9341_Read8(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  // Reinitialize D[7:0] as input GPIOs
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;

  GPIO_InitStruct.Pin = ILI9341_D0_Pin | ILI9341_D1_Pin | ILI9341_D2_Pin | ILI9341_D3_Pin;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = ILI9341_D4_Pin | ILI9341_D5_Pin | ILI9341_D6_Pin | ILI9341_D7_Pin;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  HAL_Delay(200);

  // Send read command


  HAL_Delay(200);

  // Set D[7:0] back to output GPIOs
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = ILI9341_D0_Pin | ILI9341_D1_Pin | ILI9341_D2_Pin | ILI9341_D3_Pin;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  HAL_Delay(200);
}

HAL_StatusTypeDef ILI9341_SetWriteDir(void) {}

HAL_StatusTypeDef ILI9341_SetReadDir(void) {}

HAL_StatusTypeDef ILI9341_SetLR(void) {}

HAL_StatusTypeDef ILI9341_WriteRegister8(uint8_t address, uint8_t data) {}

HAL_StatusTypeDef ILI9341_WriteRegister16(uint8_t address, uint16_t data) {}

HAL_StatusTypeDef ILI9341_WriteRegister24(uint8_t address, uint24_t data) {}

HAL_StatusTypeDef ILI9341_WriteRegister32(uint8_t address, uint32_t data) {}

HAL_StatusTypeDef ILI9341_WriteRegisterPair(uint8_t addressHigh, uint8_t addressLow, uint16_t data) {}

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
  HAL_GPIO_WritePin(ILI9341_RST_GPIO_Port, ILI9341_RST_Pin, GPIO_PIN_RESET);
  HAL_Delay(500);
  HAL_GPIO_WritePin(ILI9341_RST_GPIO_Port, ILI9341_RST_Pin, GPIO_PIN_SET);

  // Data transfer sync
  ILI9341_CS_ACTIVE;
  ILI9341_CD_DATA;
  ILI9341_Write8(0x00);
  for (uint8_t i = 0; i < 3; i++) {
    ILI9341_WR_STROBE;
  }
  ILI9341_CS_IDLE;
}
