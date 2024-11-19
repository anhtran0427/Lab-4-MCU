/*
 * queue.h
 *
 *  Created on: Nov 19, 2024
 *      Author: ASUS
 */

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_


#include "main.h"
#include "sched.h"
#define SCH_MAX_TASKS 40

typedef struct {
	int items[SCH_MAX_TASKS];
    int front;
    int rear;
} Queue;

void initializeQueue(Queue* q);
bool isEmpty(Queue* q) ;
bool isFull(Queue* q);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);



#endif /* INC_QUEUE_H_ */
