/*
 * sched.c
 *
 *  Created on: Nov 19, 2024
 *      Author: ASUS
 */
#include "sched.h"
/*unsigned char Error_code_G = 0;*/

static Queue indexQueue;

static int numTasks=0;
static int numExe=0;
sTask SCH_tasks_G[SCH_MAX_TASKS];
rearTsk EXE_tasks_G;

void SCH_Init(void) {
	unsigned char i ;
	for (i = 0; i <SCH_MAX_TASKS; i++) {
		SCH_tasks_G[i].pTask = 0x0000;
		SCH_tasks_G[i]. Delay = 0;
		SCH_tasks_G[i]. Period = 0;
		SCH_tasks_G[i].TaskID=0;
	}
	initializeQueueTsk(&EXE_tasks_G);
	initializeQueue(&indexQueue);
}

void SCH_Update(void){

	SCH_tasks_G[0].Delay=SCH_tasks_G[0].Delay-1;
	unsigned char Index=0;
	for (; Index <numTasks; Index++) {
		if (SCH_tasks_G[Index].Delay>0) break;
		else {
			sTask temp;
			temp.Delay=SCH_tasks_G[Index].Delay;
			temp.Period=SCH_tasks_G[Index].Period;
			temp.pTask=SCH_tasks_G[Index].pTask;
			temp.TaskID=SCH_tasks_G[Index].TaskID;

			enqueueTsk(&EXE_tasks_G, temp);
			numExe=numExe+1;

		}
	}
}

int SCH_Add_Task_ID(void (* pFunction) () , int DELAY, int PERIOD,int ID){
 unsigned char Index = 0;
 if (numTasks==SCH_MAX_TASKS){
	 return SCH_MAX_TASKS;
 }
 int potentialID=ID;
 // First find a gap in the array (if there is one)
 for (;Index<numTasks;Index++){
	 if(SCH_tasks_G[Index].Delay<DELAY){

		DELAY=DELAY-SCH_tasks_G[Index].Delay;
	 }
	 else {
		 for (unsigned char j=numTasks-1; j>=Index; j--){
			 SCH_tasks_G[j+1]=SCH_tasks_G[j];
             if (j==0) break;
		 }
		 SCH_tasks_G[Index].pTask = pFunction;
		 SCH_tasks_G[Index].Delay =DELAY;
		 SCH_tasks_G[Index].Period =PERIOD;
		 SCH_tasks_G[Index].TaskID=ID;
		 numTasks=numTasks+1;
		 if (Index<numTasks-1){
			 SCH_tasks_G[Index+1].Delay=SCH_tasks_G[Index+1].Delay-DELAY;
		 }
		 potentialID=-1;
		 break;
	 }
 }
 if (potentialID!=-1){
	 SCH_tasks_G[numTasks].pTask = pFunction;
	 SCH_tasks_G[numTasks].Delay =DELAY;
	 SCH_tasks_G[numTasks].Period =PERIOD;
	 SCH_tasks_G[numTasks].TaskID=ID;
	 numTasks=numTasks+1;

	 potentialID=-1;
 }
 return SCH_tasks_G[Index].TaskID;
}

int SCH_Add_Task(void (* pFunction) () , int DELAY, int PERIOD){

 unsigned char Index = 0;
 if (numTasks==SCH_MAX_TASKS){
	 return SCH_MAX_TASKS;
 }
 int potentialID=dequeue(&indexQueue);
 if (potentialID==-1){
	 return -1;
 }
 // First find a gap in the array (if there is one)
 for (;Index<numTasks;Index++){
	 if(SCH_tasks_G[Index].Delay<=DELAY){
		DELAY=DELAY-SCH_tasks_G[Index].Delay;
	 }
	 else {
		 for (unsigned char j=numTasks-1;j>=Index;j--){
			 SCH_tasks_G[j+1]=SCH_tasks_G[j];
			 if (j==0) break;
		 }
		 SCH_tasks_G[Index].pTask = pFunction;
		 SCH_tasks_G[Index].Delay =DELAY;
		 SCH_tasks_G[Index].Period =PERIOD;
		 SCH_tasks_G[Index].TaskID=potentialID;
		 numTasks=numTasks+1;
		 if (Index<numTasks-1){
			 SCH_tasks_G[Index+1].Delay=SCH_tasks_G[Index+1].Delay-DELAY;
		 }
		 potentialID=-1;
		 break;
	 }
 }
 if (potentialID!=-1){
	 SCH_tasks_G[numTasks].pTask = pFunction;
	 SCH_tasks_G[numTasks].Delay =DELAY;
	 SCH_tasks_G[numTasks].Period =PERIOD;
	 SCH_tasks_G[numTasks].TaskID=potentialID;
	 numTasks=numTasks+1;
	 potentialID=-1;
 }
 return SCH_tasks_G[Index].TaskID;
}


void SCH_Dispatch_Tasks(void){

 while (numExe>0){
	 SCH_Delete_Task_Header(1);
	 (*(EXE_tasks_G.taskList[EXE_tasks_G.front].pTask))();
	 if (EXE_tasks_G.taskList[EXE_tasks_G.front].Period > 0){

		 SCH_Add_Task_ID(EXE_tasks_G.taskList[EXE_tasks_G.front].pTask, EXE_tasks_G.taskList[EXE_tasks_G.front].Period, EXE_tasks_G.taskList[EXE_tasks_G.front].Period,EXE_tasks_G.taskList[EXE_tasks_G.front].TaskID);

	 }
	 else {
		 enqueue(&indexQueue,EXE_tasks_G.taskList[EXE_tasks_G.front].TaskID);
	 }
	 // Run the task
	 dequeueTsk(&EXE_tasks_G);

	 numExe=numExe-1;
	 if (numExe==0)break;
 }


}

int SCH_Delete_Task(int TASK_INDEX){
	unsigned char Index = 0;
	for (;Index<numTasks;Index++){
		if (SCH_tasks_G[Index].TaskID==TASK_INDEX){
			enqueue(&indexQueue,TASK_INDEX);
			for (unsigned char j=Index;j<numTasks-1;j++){
					SCH_tasks_G[j]=SCH_tasks_G[j+1];
			}
			numTasks=numTasks-1;
			return TASK_INDEX;
		}
	}
	return -1;
}

void SCH_Delete_Task_Header(int numDel){
	unsigned char Index = 0;
	for (;Index<numTasks-numDel;Index++){
		SCH_tasks_G[Index]=SCH_tasks_G[Index+numDel];
	}

	numTasks=numTasks-numDel;

}


void initializeQueueTsk(rearTsk* q)
{
    q->front =-1 ;
    q->rear=-1;
}

// Function to check if the queue is empty
bool isEmptyTsk(rearTsk* q) { return (q->front == - 1); }

// Function to check if the queue is full
bool isFullTsk(rearTsk* q) { return ((q->rear+1)%SCH_MAX_TASKS==q->front); }

// Function to add an element to the queue (Enqueue
// operation)
void enqueueTsk(rearTsk* q, sTask value)
{
    if (numExe==SCH_MAX_TASKS) {
        return;
    }
    q->rear=(q->rear+1)%SCH_MAX_TASKS;
    if (q->front==-1)q->front=0;
    q->taskList[q->rear] = value;
}

// Function to remove an element from the queue (Dequeue
// operation)
void dequeueTsk(rearTsk* q)
{
    if (isEmptyTsk(q)) {
        return;
    }
    if (q->front==q->rear){
    	q->front=-1;
    	q->rear=-1;
    }
    else {q->front=(q->front+1)%SCH_MAX_TASKS;}

}


