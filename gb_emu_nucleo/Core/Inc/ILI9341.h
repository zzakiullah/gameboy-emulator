/*
 * ILI9341.h
 *
 *  Created on: Sep 28, 2025
 *  Author: Zulaikha Zakiullah
 *
 *  Driver for Adafruit 2.8" TFT touchscreen (ILI9341)
 *  Datasheet: https://cdn-shop.adafruit.com/datasheets/ILI9341.pdf
 */

#ifndef INC_ILI9341_H_
#define INC_ILI9341_H_

#include "main.h"
#include "stm32f4xx_hal.h"

/**
 * Defines
 */

#define ILI9341_WIDTH	240
#define ILI9341_HEIGHT 	320

#define ILI9341_ID		0x9341
// Could also be 0x9328, 0x9325, 0x8357, 0x7575

// LCD controller chip identifiers
#define ID_932X 	0
#define ID_7575 	1
#define ID_9341 	2
#define ID_HX8357D 	3
#define ID_UNKNOWN 	0xFF

/**
 * Registers
 *
 * Register names from Peter Barrett's Microtouch code
 */

#define ILI9341_SOFTRESET 			0x01
#define ILI9341_SLEEPIN 			0x10
#define ILI9341_SLEEPOUT 			0x11
#define ILI9341_NORMALDISP 			0x13
#define ILI9341_INVERTOFF 			0x20
#define ILI9341_INVERTON 			0x21
#define ILI9341_GAMMASET 			0x26
#define ILI9341_DISPLAYOFF 			0x28
#define ILI9341_DISPLAYON 			0x29
#define ILI9341_COLADDRSET 			0x2A
#define ILI9341_PAGEADDRSET 		0x2B
#define ILI9341_MEMORYWRITE 		0x2C
#define ILI9341_PIXELFORMAT 		0x3A
#define ILI9341_FRAMECONTROL 		0xB1
#define ILI9341_DISPLAYFUNC 		0xB6
#define ILI9341_ENTRYMODE 			0xB7
#define ILI9341_POWERCONTROL1 		0xC0
#define ILI9341_POWERCONTROL2 		0xC1
#define ILI9341_VCOMCONTROL1 		0xC5
#define ILI9341_VCOMCONTROL2 		0xC7
#define ILI9341_MEMCONTROL 			0x36
#define ILI9341_MADCTL 				0x36

#define ILI9341_MADCTL_MY 			0x80
#define ILI9341_MADCTL_MX 			0x40
#define ILI9341_MADCTL_MV 			0x20
#define ILI9341_MADCTL_ML 			0x10
#define ILI9341_MADCTL_RGB 			0x00
#define ILI9341_MADCTL_BGR 			0x08
#define ILI9341_MADCTL_MH 			0x04

/**
 * Colors
 */

#define	ILI9341_BLACK   0x0000
#define ILI9341_GREY	0xB5B6
#define ILI9341_WHITE   0xFFFF
#define	ILI9341_BLUE    0x001F
#define	ILI9341_RED     0xF800
#define	ILI9341_GREEN   0x07E0
#define ILI9341_CYAN    0x07FF
#define ILI9341_MAGENTA 0xF81F
#define ILI9341_YELLOW  0xFFE0

/**
 * Macro functions
 *
 * Control signals are ACTIVE LOW (idle is HIGH)
 * Command/Data: LOW = command, HIGH = data
 * These are single-instruction operations and always inline
 */

#define ILI9341_RD_ACTIVE	HAL_GPIO_WritePin(ILI9341_RD_GPIO_Port, ILI9341_RD_Pin, GPIO_PIN_RESET)
#define ILI9341_RD_IDLE 	HAL_GPIO_WritePin(ILI9341_RD_GPIO_Port, ILI9341_RD_Pin, GPIO_PIN_SET)
#define ILI9341_WR_ACTIVE 	HAL_GPIO_WritePin(ILI9341_WR_GPIO_Port, ILI9341_WR_Pin, GPIO_PIN_RESET)
#define ILI9341_WR_IDLE 	HAL_GPIO_WritePin(ILI9341_WR_GPIO_Port, ILI9341_WR_Pin, GPIO_PIN_SET)
#define ILI9341_CD_COMMAND 	HAL_GPIO_WritePin(ILI9341_CD_GPIO_Port, ILI9341_CD_Pin, GPIO_PIN_RESET)
#define ILI9341_CD_DATA 	HAL_GPIO_WritePin(ILI9341_CD_GPIO_Port, ILI9341_CD_Pin, GPIO_PIN_SET)
#define ILI9341_CS_ACTIVE 	HAL_GPIO_WritePin(ILI9341_CS_GPIO_Port, ILI9341_CS_Pin, GPIO_PIN_RESET)
#define ILI9341_CS_IDLE 	HAL_GPIO_WritePin(ILI9341_CS_GPIO_Port, ILI9341_CS_Pin, GPIO_PIN_SET)

#define ILI9341_RD_STROBE	\
  {							\
    ILI9341_RD_ACTIVE;		\
    ILI9341_RD_IDLE;		\
  }

#define ILI9341_WR_STROBE	\
  {							\
    ILI9341_WR_ACTIVE;		\
    ILI9341_WR_IDLE;		\
  }

/**
 * Functions
 */

void ILI9341_SetDataRead(void);
void ILI9341_SetDataWrite(void);

void ILI9341_SendReadCommand(void);

void ILI9341_Write8(uint8_t value);
uint8_t ILI9341_Read8(void);

void ILI9341_WriteRegister8(uint8_t address, uint8_t data);
void ILI9341_WriteRegister16(uint16_t address, uint16_t data);
void ILI9341_WriteRegister32(uint8_t address, uint32_t data);
void ILI9341_WriteRegisterPair(uint8_t addressHigh, uint8_t addressLow, uint16_t data);
uint32_t ILI9341_ReadRegister(uint8_t reg);

void ILI9341_SetAddressWindow(int x1, int y1, int x2, int y2);

HAL_StatusTypeDef ILI9341_ReadID(void);
HAL_StatusTypeDef ILI9341_Init(void);
void ILI9341_Reset(void);

void ILI9341_DrawPixel(int16_t x, int16_t y, uint16_t color);
void ILI9341_FillScreen(uint16_t color);
void ILI9341_Flood(uint16_t color, uint32_t len);

#endif /* INC_ILI9341_H_ */
