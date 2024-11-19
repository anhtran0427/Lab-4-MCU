/*
 * queue.c
 *
 *  Created on: Nov 19, 2024
 *      Author: ASUS
 */


#include "queue.h"
void initializeQueue(Queue* q)
{
    q->front =0 ;
    q->rear = SCH_MAX_TASKS;
    int i ;
    for (i = 0; i <SCH_MAX_TASKS; i++) {
    	q->items[i]=i;
    }
}

// Function to check if the queue is empty
bool isEmpty(Queue* q) { return (q->front == - 1)&&(q->rear==-1); }

// Function to check if the queue is full
bool isFull(Queue* q) { return ((q->rear+1)%SCH_MAX_TASKS==q->front); }

// Function to add an element to the queue (Enqueue
// operation)
void enqueue(Queue* q, int value)
{
    if (isFull(q)) {
        return;
    }
    q->rear=(q->rear+1)%SCH_MAX_TASKS;
    if (q->front==-1)q->front=0;
    q->items[q->rear] = value;
}

// Function to remove an element from the queue (Dequeue
// operation)
int dequeue(Queue* q)
{
    if (isEmpty(q)) {
        return -1;
    }
    int result=q->items[q->front];
    if (q->front==q->rear){
    	q->front=-1;
    	q->rear=-1;
    }
    q->front=(q->front+1)%SCH_MAX_TASKS;
    return result;
}
