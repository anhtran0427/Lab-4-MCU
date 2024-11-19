/*
 * timer.c
 *
 *  Created on: Nov 19, 2024
 *      Author: ASUS
 */
#include "timer.h"

void timerInit(){}
static int i=0;
static int j=0;
int timerFlag=0;
void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim )
{

	j++;

	SCH_Update();

	if (j==400){
			timerFlag=1;
	}
 }
