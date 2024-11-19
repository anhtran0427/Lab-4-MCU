/*
 * led.c
 *
 *  Created on: Nov 19, 2024
 *      Author: ASUS
 */
#include "led.h"

void toggle_1(){
	HAL_GPIO_TogglePin(Tsk1_GPIO_Port, Tsk1_Pin);
}
void toggle_2(){
	HAL_GPIO_TogglePin(Tsk2_GPIO_Port, Tsk2_Pin);
}
void toggle_3(){
	HAL_GPIO_TogglePin(Tsk3_GPIO_Port, Tsk3_Pin);
}
void toggle_4(){
	HAL_GPIO_TogglePin(Tsk4_GPIO_Port, Tsk4_Pin);
}
void toggle_5(){
	HAL_GPIO_TogglePin(Tsk5_GPIO_Port, Tsk5_Pin);
}

