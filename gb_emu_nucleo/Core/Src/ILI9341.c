/*
 * ILI9341.c
 *
 *  Created on: Sep 28, 2025
 *  Author: Zulaikha Zakiullah
 *
 *  Driver for Adafruit 2.8" TFT touchscreen (ILI9341)
 *  Datasheet: https://cdn-shop.adafruit.com/datasheets/ILI9341.pdf
 */

#include <ILI9341.h>

HAL_StatusTypeDef ILI9341_SetDataInput(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;

  GPIO_InitStruct.Pin = ILI9341_D0_Pin | ILI9341_D1_Pin | ILI9341_D2_Pin | ILI9341_D3_Pin;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = ILI9341_D4_Pin | ILI9341_D5_Pin | ILI9341_D6_Pin | ILI9341_D7_Pin;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  HAL_Delay(200);
}

HAL_StatusTypeDef ILI9341_SetDataOutput(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  GPIO_InitStruct.Pin = ILI9341_D0_Pin | ILI9341_D1_Pin | ILI9341_D2_Pin | ILI9341_D3_Pin;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = ILI9341_D4_Pin | ILI9341_D5_Pin | ILI9341_D6_Pin | ILI9341_D7_Pin;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  HAL_Delay(200);
}

void ILI9341_SendReadCommand(void) {
  ILI9341_CD_COMMAND;
  ILI9341_RD_IDLE;
  ILI9341_WR_IDLE;
}

HAL_StatusTypeDef ILI9341_Write8(uint8_t value) {}

uint8_t ILI9341_Read8(void) {
  ILI9341_RD_ACTIVE;
//  HAL_Delay(10);
  ILI9341_RD_IDLE;
  uint8_t data =
    (HAL_GPIO_ReadPin(ILI9341_D7_GPIO_Port, ILI9341_D7_Pin) << 7) |
	(HAL_GPIO_ReadPin(ILI9341_D6_GPIO_Port, ILI9341_D6_Pin) << 6) |
	(HAL_GPIO_ReadPin(ILI9341_D5_GPIO_Port, ILI9341_D5_Pin) << 5) |
	(HAL_GPIO_ReadPin(ILI9341_D4_GPIO_Port, ILI9341_D4_Pin) << 4) |
	(HAL_GPIO_ReadPin(ILI9341_D3_GPIO_Port, ILI9341_D3_Pin) << 3) |
	(HAL_GPIO_ReadPin(ILI9341_D2_GPIO_Port, ILI9341_D2_Pin) << 2) |
	(HAL_GPIO_ReadPin(ILI9341_D1_GPIO_Port, ILI9341_D1_Pin) << 1) |
	HAL_GPIO_ReadPin(ILI9341_D0_GPIO_Port, ILI9341_D0_Pin);

  return data;
}

HAL_StatusTypeDef ILI9341_SetWriteDir(void) {}

HAL_StatusTypeDef ILI9341_SetReadDir(void) {}

HAL_StatusTypeDef ILI9341_SetLR(void) {}

HAL_StatusTypeDef ILI9341_WriteRegister8(uint8_t address, uint8_t data) {}

HAL_StatusTypeDef ILI9341_WriteRegister16(uint8_t address, uint16_t data) {}

HAL_StatusTypeDef ILI9341_WriteRegister24(uint8_t address, uint24_t data) {}

HAL_StatusTypeDef ILI9341_WriteRegister32(uint8_t address, uint32_t data) {}

HAL_StatusTypeDef ILI9341_WriteRegisterPair(uint8_t addressHigh, uint8_t addressLow, uint16_t data) {}

HAL_StatusTypeDef ILI9341_SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {}

HAL_StatusTypeDef ILI9341_Init(void) {
  // Read and verify ID
  const id = 0;
  if (id != ILI9341_ID) {
    return HAL_ERROR;
  }

  ILI9341_SetDataInput();
  ILI9341_SendReadCommand();

  // 1st parameter - dummy data
  ILI9341_Read8();

  // 2nd parameter - ID1 (manufacturer ID)
  uint8_t id1 = ILI9341_Read8();

  // 3rd parameter - ID2 (module/driver version ID)
  uint8_t id2 = ILI9341_Read8();

  // 4th parameter - ID3 (module/driver ID)
  uint8_t id3 = ILI9341_Read8();

  ILI9341_SetDataOutput();

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
