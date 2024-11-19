/*
 * sched.h
 *
 *  Created on: Nov 19, 2024
 *      Author: ASUS
 */

#ifndef INC_SCHED_H_
#define INC_SCHED_H_

#include "main.h"
#include "queue.h"
#define SCH_MAX_TASKS 40

typedef struct {
void ( * pTask)(void) ;
int Delay;
int Period;
int TaskID;
} sTask;

typedef struct {
	sTask taskList[SCH_MAX_TASKS];
    int front;
    int rear;
} rearTsk;


extern sTask SCH_tasks_G[SCH_MAX_TASKS];
extern rearTsk EXE_tasks_G;

int SCH_Delete_Task(int TASK_INDEX);
void SCH_Delete_Task_Header(int numDel);
int SCH_Delete_Task_Marking(int TASK_INDEX);
void SCH_Dispatch_Tasks(void);
int SCH_Add_Task(void (* pFunction) () , int DELAY, int PERIOD);
int SCH_Add_Task_ID(void (* pFunction) () , int DELAY, int PERIOD,int ID);
void SCH_Update(void);
void SCH_Init(void);

void initializeQueueTsk(rearTsk* q);
bool isEmptyTsk(rearTsk* q) ;
bool isFullTsk(rearTsk* q);
void enqueueTsk(rearTsk* q, sTask Task);
void dequeueTsk(rearTsk* q);

#endif /* INC_SCHED_H_ */
