#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "maze.h"

#define QueueMaxSize 100

typedef char QueueType;

typedef struct SeqQueue
{
        QueueType data[QueueMaxSize];
        size_t tail;
        size_t head;
        size_t size;
}SeqQueue;

void SeqQueueInit(SeqQueue* q);

void SeqQueueDestory(SeqQueue* q);

void SeqQueuePush(SeqQueue* q, QueueType value);

void SeqQueuePop(SeqQueue* q);

int SeqQueueFront(SeqQueue* q, QueueType* value);

size_t SeqQueueSize(SeqQueue* q);

typedef struct Point SeqStackType;

#define SeqStackMaxSize 1000

typedef struct SeqStack
{
        SeqStackType data[SeqStackMaxSize];
        size_t size;
}SeqStack;

void SeqStackInit(SeqStack* stack);

void SeqSatckDestory(SeqStack* stack);

void SeqStackPush(SeqStack* stack, SeqStackType value);

void SeqStackPop(SeqStack* stack);

int SeqStackTop(SeqStack* stack, SeqStackType* value);

size_t SeqStackSize(SeqStack* stack);

void SeqStackAssign(SeqStack* dst,SeqStack* src);

void SeqStackDebugPrint(SeqStack* stack);
