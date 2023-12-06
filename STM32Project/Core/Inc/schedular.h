/*
 * schedular.h
 *
 *  Created on: Nov 23, 2023
 *      Author: Admin
 */

#ifndef INC_SCHEDULAR_H_
#define INC_SCHEDULAR_H_

#include "global.h"

typedef struct {
	void (*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint32_t RunMe;
	uint32_t TaskID;
} sTask;

#define SCH_MAX_TASKS 	40
#define NO_TASK_ID		0
#define TICK 			10

void SCH_Init(void);
void SCH_Update(void);
uint32_t SCH_Add_Task(void (*pFuntion)(), uint32_t DELAY, uint32_t PERIOD);
void SCH_Dispatch_Tasks(void);
uint8_t SCH_Delete_Task(uint32_t TASK_INDEX);

#endif /* INC_SCHEDULAR_H_ */
