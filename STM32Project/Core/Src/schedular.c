/*
 * schedular.c
 *
 *  Created on: Nov 23, 2023
 *      Author: Admin
 */
#include "schedular.h"

sTask SCH_task_G[SCH_MAX_TASKS];

void SCH_Init(void){
	uint32_t i;
	for (i = 0; i < SCH_MAX_TASKS; i++){
		SCH_Delete_Task(i);
	}
}

void SCH_Update(void){
	uint32_t Index;
	for(Index = 0; Index < SCH_MAX_TASKS; Index++){
		if(SCH_task_G[Index].pTask){
			if(SCH_task_G[Index].Delay == 0){
				SCH_task_G[Index].RunMe += 1;
				if(SCH_task_G[Index].Period){
					SCH_task_G[Index].Delay = SCH_task_G[Index].Period;
				}
			} else {
				SCH_task_G[Index].Delay -= 1;
			}
		}
	}
}

uint32_t SCH_Add_Task(void (*pFuntion)(), uint32_t DELAY, uint32_t PERIOD){
	uint32_t Index = 0;
	while ((SCH_task_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS)) {
		Index++;
	}
	if (Index == SCH_MAX_TASKS){
		return 0;
	}

	SCH_task_G[Index].pTask = pFuntion;
	SCH_task_G[Index].Delay = DELAY/TICK;
	SCH_task_G[Index].Period = PERIOD/TICK;
	SCH_task_G[Index].RunMe = 0;
	SCH_task_G[Index].TaskID = Index;
	return SCH_task_G[Index].TaskID;
}

void SCH_Dispatch_Tasks(void){
	uint32_t Index;
	for (Index = 0; Index < SCH_MAX_TASKS; Index++){
		if(SCH_task_G[Index].RunMe > 0) {
			(*SCH_task_G[Index].pTask)();
			SCH_task_G[Index].RunMe -= 1;
			if(SCH_task_G[Index].Period == 0){
				SCH_Delete_Task(Index);
			}
		}
	}
}

uint8_t SCH_Delete_Task(uint32_t TASK_INDEX){
	SCH_task_G[TASK_INDEX].pTask = 0x0000;
	SCH_task_G[TASK_INDEX].Delay = 0;
	SCH_task_G[TASK_INDEX].Period = 0;
	SCH_task_G[TASK_INDEX].RunMe = 0;
	return TASK_INDEX;
}
