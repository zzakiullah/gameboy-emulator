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

void ILI9341_SetDataRead(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;

  GPIO_InitStruct.Pin = ILI9341_D0_Pin | ILI9341_D1_Pin | ILI9341_D2_Pin | ILI9341_D3_Pin;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = ILI9341_D4_Pin | ILI9341_D5_Pin | ILI9341_D6_Pin | ILI9341_D7_Pin;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  HAL_Delay(100);
}

void ILI9341_SetDataWrite(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  GPIO_InitStruct.Pin = ILI9341_D0_Pin | ILI9341_D1_Pin | ILI9341_D2_Pin | ILI9341_D3_Pin;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = ILI9341_D4_Pin | ILI9341_D5_Pin | ILI9341_D6_Pin | ILI9341_D7_Pin;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  HAL_Delay(100);
}

void ILI9341_SendReadCommand(void) {
  ILI9341_CD_COMMAND;
  ILI9341_RD_IDLE;
  ILI9341_WR_IDLE;
}

void ILI9341_Write8(uint8_t value) {
  // Write 8-bit value to LCD data lines
  HAL_GPIO_WritePin(ILI9341_D7_GPIO_Port, ILI9341_D7_Pin, (value & 0x40) >> 7);
  HAL_GPIO_WritePin(ILI9341_D6_GPIO_Port, ILI9341_D6_Pin, (value & 0x20) >> 6);
  HAL_GPIO_WritePin(ILI9341_D5_GPIO_Port, ILI9341_D5_Pin, (value & 0x10) >> 5);
  HAL_GPIO_WritePin(ILI9341_D4_GPIO_Port, ILI9341_D4_Pin, (value & 0x0F) >> 4);
  HAL_GPIO_WritePin(ILI9341_D3_GPIO_Port, ILI9341_D3_Pin, (value & 0x08) >> 3);
  HAL_GPIO_WritePin(ILI9341_D2_GPIO_Port, ILI9341_D2_Pin, (value & 0x04) >> 2);
  HAL_GPIO_WritePin(ILI9341_D1_GPIO_Port, ILI9341_D1_Pin, (value & 0x02) >> 1);
  HAL_GPIO_WritePin(ILI9341_D0_GPIO_Port, ILI9341_D0_Pin, (value & 0x01));
  ILI9341_WR_STROBE;
}

uint8_t ILI9341_Read8(void) {
  // Read 8-bit value from LCD data lines
  ILI9341_RD_STROBE;
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

void ILI9341_WriteRegister8(uint8_t address, uint8_t data) {
  ILI9341_CD_COMMAND;
  ILI9341_Write8(address);
  ILI9341_CD_DATA;
  ILI9341_Write8(data);
}

void ILI9341_WriteRegister16(uint16_t address, uint16_t data) {
  uint8_t high = address >> 8;
  uint8_t low = address;

  ILI9341_CD_COMMAND;
  ILI9341_Write8(high);
  ILI9341_Write8(low);

  high = data >> 8;
  low = data;

  ILI9341_CD_DATA;
  ILI9341_Write8(high);
  ILI9341_Write8(low);
}

void ILI9341_WriteRegister32(uint8_t address, uint32_t data) {
  ILI9341_CS_ACTIVE;
  ILI9341_CD_COMMAND;
  ILI9341_Write8(address);
  ILI9341_CD_DATA;

//  delayMicroseconds(10);
  ILI9341_Write8(data >> 24);

//  delayMicroseconds(10);
  ILI9341_Write8(data >> 16);

//  delayMicroseconds(10);
  ILI9341_Write8(data >> 8);

//  delayMicroseconds(10);
  ILI9341_Write8(data);
  ILI9341_CS_IDLE;
}

void ILI9341_WriteRegisterPair(uint8_t addressHigh, uint8_t addressLow, uint16_t data) {
  // Set value of 2 TFT registers: Two 8-bit addresses (high & low), 16-bit value
  uint8_t dataHigh = data >> 8;
  uint8_t dataLow = data;

  ILI9341_CD_COMMAND;
  ILI9341_Write8(addressHigh);
  ILI9341_CD_DATA;
  ILI9341_Write8(dataHigh);
  ILI9341_CD_COMMAND;
  ILI9341_Write8(addressLow);
  ILI9341_CD_DATA;
  ILI9341_Write8(dataLow);
}

uint32_t ILI9341_ReadRegister(uint8_t reg) {
  uint32_t id;
  uint8_t x;

  // Try reading register #4
  ILI9341_CS_ACTIVE;
  ILI9341_CD_COMMAND;
  ILI9341_Write8(reg);
  ILI9341_SetDataRead(); // Set up LCD data port(s) for READ operations
  ILI9341_CD_DATA;
//  delayMicroseconds(50);

  x = ILI9341_Read8();
  id = x;
  id <<= 8;

  x = ILI9341_Read8();
  id |= x;
  id <<= 8;

  x = ILI9341_Read8();
  id |= x;
  id <<= 8;

  x = ILI9341_Read8();
  id |= x;

  ILI9341_CS_IDLE;
  ILI9341_SetDataWrite(); // Restore LCD data port(s) to WRITE configuration

  return id;
}

void ILI9341_SetAddressWindow(int x1, int y1, int x2, int y2) {
  /**
   * Sets the LCD address window (and address counter, on 932X).
   * Relevant to rect/screen fills and H/V lines.  Input coordinates are
   * assumed pre-sorted (e.g. x2 >= x1).
   */
  ILI9341_CS_ACTIVE;

  uint32_t t;
  t = x1;
  t <<= 16;
  t |= x2;
  ILI9341_WriteRegister32(ILI9341_COLADDRSET, t);
  t = y1;
  t <<= 16;
  t |= y2;
  ILI9341_WriteRegister32(ILI9341_PAGEADDRSET, t);

  ILI9341_CS_IDLE;
}

HAL_StatusTypeDef ILI9341_ReadID(void) {
  uint16_t id;

  // Retry a bunch!
  for (int i = 0; i < 5; i++) {
    id = (uint16_t)ILI9341_ReadRegister(0xD3);
//    delayMicroseconds(50);
    if (id == ILI9341_ID) {
      return HAL_OK;
    }
  }
  return HAL_ERROR;
}

HAL_StatusTypeDef ILI9341_Init(void) {
  ILI9341_SetDataRead();
  ILI9341_SendReadCommand();

  if (ILI9341_ReadID() != HAL_OK) {
    return HAL_ERROR;
  }

  ILI9341_SetDataWrite();

  ILI9341_CS_ACTIVE;
  ILI9341_WriteRegister8(ILI9341_SOFTRESET, 0);
  HAL_Delay(50);
  ILI9341_WriteRegister8(ILI9341_DISPLAYOFF, 0);

  ILI9341_WriteRegister8(ILI9341_POWERCONTROL1, 0x23);
  ILI9341_WriteRegister8(ILI9341_POWERCONTROL2, 0x10);
  ILI9341_WriteRegister16(ILI9341_VCOMCONTROL1, 0x2B2B);
  ILI9341_WriteRegister8(ILI9341_VCOMCONTROL2, 0xC0);
  ILI9341_WriteRegister8(ILI9341_MEMCONTROL, ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR);
  ILI9341_WriteRegister8(ILI9341_PIXELFORMAT, 0x55);
  ILI9341_WriteRegister16(ILI9341_FRAMECONTROL, 0x001B);

  ILI9341_WriteRegister8(ILI9341_ENTRYMODE, 0x07);
  /* ILI9341_WriteRegister32(ILI9341_DISPLAYFUNC, 0x0A822700);*/

  ILI9341_WriteRegister8(ILI9341_SLEEPOUT, 0);
  HAL_Delay(150);
  ILI9341_WriteRegister8(ILI9341_DISPLAYON, 0);
  HAL_Delay(500);
  ILI9341_SetAddressWindow(0, 0, ILI9341_WIDTH - 1, ILI9341_HEIGHT - 1);

  return HAL_OK;
}

void ILI9341_Reset(void) {
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

void ILI9341_DrawPixel(int16_t x, int16_t y, uint16_t color) {
  if ((x < 0) || (y < 0) || (x >= ILI9341_WIDTH) || (y >= ILI9341_HEIGHT)) {
    return;
  }

  ILI9341_CS_ACTIVE;

  ILI9341_SetAddressWindow(x, y, ILI9341_WIDTH - 1, ILI9341_HEIGHT - 1);
  ILI9341_CS_ACTIVE;
  ILI9341_CD_COMMAND;
  ILI9341_Write8(0x2C);
  ILI9341_CD_DATA;
  ILI9341_Write8(color >> 8);
  ILI9341_Write8(color);

  ILI9341_CS_IDLE;
}

void ILI9341_FillScreen(uint16_t color) {
  ILI9341_SetAddressWindow(0, 0, ILI9341_WIDTH - 1, ILI9341_HEIGHT - 1);
  ILI9341_Flood(color, (long)ILI9341_WIDTH * (long)ILI9341_HEIGHT);
}

void ILI9341_Flood(uint16_t color, uint32_t len) {
  /**
   * Fast block fill operation for fillScreen, fillRect, H/V line, etc.
   * Requires setAddrWindow() has previously been called to set the fill
   * bounds. 'len' is inclusive, MUST be >= 1.
   */
  uint16_t blocks;
  uint8_t i, colorHigh = color >> 8, colorLow = color;

  ILI9341_CS_ACTIVE;
  ILI9341_CD_COMMAND;
  ILI9341_Write8(0x2C);

  // Write first pixel normally, decrement counter by 1
  ILI9341_CD_DATA;
  ILI9341_Write8(colorHigh);
  ILI9341_Write8(colorLow);
  len--;

  blocks = (uint16_t)(len / 64); // 64 pixels/block
  if (colorHigh == colorLow) {
    // High and low bytes are identical.  Leave prior data
    // on the port(s) and just toggle the write strobe.
    while (blocks--) {
      i = 16; // 64 pixels/block / 4 pixels/pass
      do {
        ILI9341_WR_STROBE;
	    ILI9341_WR_STROBE;
        ILI9341_WR_STROBE;
        ILI9341_WR_STROBE; // 2 bytes/pixel
        ILI9341_WR_STROBE;
        ILI9341_WR_STROBE;
        ILI9341_WR_STROBE;
        ILI9341_WR_STROBE; // x 4 pixels
      } while (--i);
    }
    // Fill any remaining pixels (1 to 64)
    for (i = (uint8_t)len & 63; i--;) {
      ILI9341_WR_STROBE;
      ILI9341_WR_STROBE;
    }
  } else {
    while (blocks--) {
	  i = 16; // 64 pixels/block / 4 pixels/pass
	  do {
        ILI9341_Write8(colorHigh);
        ILI9341_Write8(colorLow);
        ILI9341_Write8(colorHigh);
        ILI9341_Write8(colorLow);
        ILI9341_Write8(colorHigh);
        ILI9341_Write8(colorLow);
        ILI9341_Write8(colorHigh);
        ILI9341_Write8(colorLow);
      } while (--i);
    }
    for (i = (uint8_t)len & 63; i--;) {
      ILI9341_Write8(colorHigh);
      ILI9341_Write8(colorLow);
    }
  }
  ILI9341_CS_IDLE;
}
