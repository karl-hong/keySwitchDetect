/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */
#include <stdio.h>
#include "common.h"
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */
typedef struct{
  GPIO_TypeDef *port;
  uint16_t pin;
}pin_t;

pin_t LS[]={
  {LS7_GPIO_Port, LS7_Pin},//1å? 
  {LS1_GPIO_Port, LS1_Pin},//2å?
  {LS2_GPIO_Port, LS2_Pin},//3å?
  {LS3_GPIO_Port, LS3_Pin},//4å?
  {LS4_GPIO_Port, LS4_Pin},//5å? 
  {LS5_GPIO_Port, LS5_Pin},//6å? 
  {LS6_GPIO_Port, LS6_Pin},//7å? 
  {LS8_GPIO_Port, LS8_Pin},//8å? 
  {LS9_GPIO_Port, LS9_Pin},//9å? 
  {LS10_GPIO_Port, LS10_Pin},//10å?
  {LS20_GPIO_Port, LS20_Pin},//11å?
  {LS19_GPIO_Port, LS19_Pin},//12å?
  {LS18_GPIO_Port, LS18_Pin},//13å?
  {LS17_GPIO_Port, LS17_Pin},//14å?
  {LS16_GPIO_Port, LS16_Pin},//15å?
  {LS15_GPIO_Port, LS15_Pin},//16å?
  {LS14_GPIO_Port, LS14_Pin},//17å?
  {LS13_GPIO_Port, LS13_Pin},//18å?
  {LS12_GPIO_Port, LS12_Pin},//19å?
  {LS11_GPIO_Port, LS11_Pin},//20å? 
};

pin_t Det[]={
  {Det7_GPIO_Port, Det7_Pin},//1å?
  {Det1_GPIO_Port, Det1_Pin},//2å?
  {Det2_GPIO_Port, Det2_Pin},//3å?
  {Det3_GPIO_Port, Det3_Pin},//4å?
  {Det4_GPIO_Port, Det4_Pin},//5å?
  {Det5_GPIO_Port, Det5_Pin},//6å?
  {Det6_GPIO_Port, Det6_Pin},//7å?
  {Det8_GPIO_Port, Det8_Pin},//8å?
  {Det9_GPIO_Port, Det9_Pin},//9å?
  {Det10_GPIO_Port, Det10_Pin},//10å?
  {Det20_GPIO_Port, Det20_Pin},//11å?
  {Det19_GPIO_Port, Det19_Pin},//12å?
  {Det18_GPIO_Port, Det18_Pin},//13å?
  {Det17_GPIO_Port, Det17_Pin},//14å?
  {Det16_GPIO_Port, Det16_Pin},//15å?
  {Det15_GPIO_Port, Det15_Pin},//16å?
  {Det14_GPIO_Port, Det14_Pin},//17å?
  {Det13_GPIO_Port, Det13_Pin},//18å?
  {Det12_GPIO_Port, Det12_Pin},//19å?
  {Det11_GPIO_Port, Det11_Pin},//20å? 
};
/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LS1_Pin|LS3_Pin|LS4_Pin|ChargeEnable_Pin
                          |LS8_Pin|LS13_Pin|LS14_Pin|LS18_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, LS2_Pin|LS6_Pin|LS16_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LS5_Pin|LS15_Pin|LS17_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LS9_Pin|LS10_Pin|LS11_Pin|LS12_Pin
                          |LS20_Pin|LS7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LS19_GPIO_Port, LS19_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LS1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LS1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PCPin PCPin PCPin PCPin
                           PCPin PCPin PCPin PCPin */
  GPIO_InitStruct.Pin = ChargeStatus_Pin|DoneStatus_Pin|Det2_Pin|Det3_Pin
                          |Det13_Pin|Det14_Pin|Det17_Pin|Det18_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PFPin PFPin PFPin */
  GPIO_InitStruct.Pin = Det1_Pin|Det5_Pin|Det16_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : PFPin PFPin PFPin */
  GPIO_InitStruct.Pin = LS2_Pin|LS6_Pin|LS16_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : PCPin PCPin PCPin PCPin
                           PCPin PCPin PCPin */
  GPIO_InitStruct.Pin = LS3_Pin|LS4_Pin|ChargeEnable_Pin|LS8_Pin
                          |LS13_Pin|LS14_Pin|LS18_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = Det4_Pin|Det6_Pin|Det15_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin */
  GPIO_InitStruct.Pin = LS5_Pin|LS17_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin
                           PBPin PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = Det8_Pin|Det9_Pin|Det10_Pin|Det11_Pin
                          |Det12_Pin|Det19_Pin|Det20_Pin|Det7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin
                           PBPin */
  GPIO_InitStruct.Pin = LS9_Pin|LS10_Pin|LS11_Pin|LS12_Pin
                          |LS7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LS15_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LS15_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LS19_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LS19_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LS20_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LS20_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin */
  GPIO_InitStruct.Pin = RC1_Pin|RC2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /**/
  HAL_I2CEx_EnableFastModePlus(SYSCFG_CFGR1_I2C_FMP_PB8);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

}

/* USER CODE BEGIN 2 */
void user_set_charge_enable(uint8_t status)
{
	HAL_GPIO_WritePin(ChargeEnable_GPIO_Port, ChargeEnable_Pin, status ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void user_set_output(uint8_t out, uint8_t status)
{
  if(out >= sizeof(LS)/sizeof(pin_t))  return;

  HAL_GPIO_WritePin(LS[out].port, LS[out].pin, status ? GPIO_PIN_SET : GPIO_PIN_RESET);

}

int user_get_input(uint8_t input)
{
  if(input >= sizeof(Det)/sizeof(pin_t))  return -1;

  return (uint8_t)HAL_GPIO_ReadPin(Det[input].port, Det[input].pin);
}

void user_check_device_status(void)
{
	if(myDevice.checkPeriod) return;
	
	for(int i=0;i<DEV_NUM;i++){
		myDevice.devCtrl[i].port = i;

		myDevice.devCtrl[i].lastOutState = user_get_input(i);

		if(myDevice.devCtrl[i].outState != myDevice.devCtrl[i].lastOutState){
			
			myDevice.devCtrl[i].outCnt ++;
			
			if(myDevice.devCtrl[i].outCnt >= 5){
				myDevice.devCtrl[i].outState = myDevice.devCtrl[i].lastOutState;
					
				if(myDevice.autoReportFlag && myDevice.devCtrl[i].outStateInitFlag){
					myDevice.cmdControl.autoAlarm.sendCmdEnable = CMD_ENABLE;
					myDevice.cmdControl.autoAlarm.sendCmdDelay = 0;
					myDevice.repCtrl[i].enable = CMD_ENABLE;
					myDevice.repCtrl[i].type = myDevice.devCtrl[i].outState;
				}
				
				myDevice.devCtrl[i].outStateInitFlag = 1;
				myDevice.devCtrl[i].outCnt = 0;
			}	
		}else{
			myDevice.devCtrl[i].outCnt = 0;
		}
	
	}

	myDevice.checkPeriod = 10;//50ms
}

static void red_led_flash(dev_ctrl_t *dev_ctr)
{
	if(0 < dev_ctr->ledFlashCnt) return;

	dev_ctr->flashStatus = !dev_ctr->flashStatus;

	user_set_output(dev_ctr->port, dev_ctr->flashStatus);

	dev_ctr->ledFlashCnt = FLASH_FREQ;
}

static void green_led_flash(dev_ctrl_t *dev_ctr)
{
	if(0 < dev_ctr->ledFlashCnt) return;

	dev_ctr->flashStatus = !dev_ctr->flashStatus;

	user_set_output(dev_ctr->port, dev_ctr->flashStatus);

	dev_ctr->ledFlashCnt = FLASH_FREQ;
}

static void red_green_led_flash(dev_ctrl_t *dev_ctr)
{
	if(0 < dev_ctr->ledFlashCnt) return;
	
	dev_ctr->flashStatus = !dev_ctr->flashStatus;

	user_set_output(dev_ctr->port, dev_ctr->flashStatus);

	dev_ctr->ledFlashCnt = FLASH_FREQ;
}

static void led_auto_mode(dev_ctrl_t *dev_ctr)
{
	if(dev_ctr->outState){
		/* è®¾å¤‡åœ¨ä½*/
		user_set_output(dev_ctr->port, LED_GREEN_ON);
	}else{
		/* è®¾å¤‡ä¸åœ¨ï¿½? */
		user_set_output(dev_ctr->port, LED_RED_ON);
	}
}

static void led_manual_mode(dev_ctrl_t *dev_ctr)
{
	switch(dev_ctr->ledState){
		case LED_STATE_OFF:{
			break;
		}

		case LED_STATE_RED_ON:{
			user_set_output(dev_ctr->port, LED_RED_ON);
			break;
		}

		case LED_STATE_GREEN_ON:{
			user_set_output(dev_ctr->port, LED_GREEN_ON);
			break;
		}

		case LED_STATE_RED_FLASH:{
			red_led_flash(dev_ctr);
			break;
		}

		case LED_STATE_GREEN_FLASH:{
			green_led_flash(dev_ctr);
			break;
		}

		case LED_STATE_RED_GREEN_FLASH:{
			red_green_led_flash(dev_ctr);
			break;
		}

		default:break;
	}
}

static void _led_task(dev_ctrl_t *dev_ctr)
{
	switch(dev_ctr->mode){
		case LED_MODE_AUTO:{
			led_auto_mode(dev_ctr);
			break;
		}

		case LED_MODE_MANUAL:{
			led_manual_mode(dev_ctr);
			break;
		}

		default:break;
	}
}

void user_led_task(void)
{
	for(int i=0;i<DEV_NUM;i++){
		myDevice.devCtrl[i].port = i;
		_led_task(&myDevice.devCtrl[i]);
	}
}

/* USER CODE END 2 */
