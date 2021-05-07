/* 
 * File:   Queue.h
 * Author: Shuuya Monzen
 *
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// <editor-fold defaultstate="collapsed" desc="サイズ定義">
#define MAX_DATA_TYPE_QUEUE_SIZE 30
#define MAX_DATA_TYPE_QUEUE_INDEX (MAX_DATA_TYPE_QUEUE_SIZE-1)

#define MAX_ADDRESS_TYPE_QUEUE_SIZE 30
#define MAX_ADDRESS_TYPE_QUEUE_INDEX (MAX_ADDRESS_TYPE_QUEUE_SIZE-1)
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="定数定義">
typedef enum  {
    ValueType_Queue,
    ReferenceType_Queue
} QueueType;

typedef enum{
    IsIdle_Queue,
    IsBusy_Queue,
}QueueStatus;
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="クラス定義">
typedef struct {
    volatile unsigned int* IE_BytePointer;
    uint8_t bitNum;
} QueueInterrupt;

typedef struct queue Queue;
struct queue{
    // <editor-fold defaultstate="collapsed" desc="プロパティ">
    uint8_t dataArrary[MAX_DATA_TYPE_QUEUE_SIZE];
    void* addressArray[MAX_ADDRESS_TYPE_QUEUE_SIZE];
    
    QueueInterrupt queueInterruptObj;
    QueueStatus status;
    QueueType type;
    uint8_t headPosition;
    uint8_t taiPosition;
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="メソッド">
    void (*initQueue)(Queue* queue);
    void  (*enqueueBasic)(Queue* queue, void* datas);
    void*  (*dequeueBasic)(Queue* queue);
    void  (*queueInterruptOff)(QueueInterrupt* queueInterruptObj);
    void  (*queueInterruptOn)(QueueInterrupt* queueInterruptObj);
    // </editor-fold>
};
// </editor-fold>

#endif

