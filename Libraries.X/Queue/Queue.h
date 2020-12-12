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

// <editor-fold defaultstate="collapsed" desc="関数ポインタ型定義">
typedef void (*FuncEnqueue)(uint8_t byte);
// </editor-fold>

typedef struct {
    // <editor-fold defaultstate="collapsed" desc="プロパティ">
    uint8_t DataArrary[MAX_QUEUE_SIZE_DATA_TYPE];
    
    QueueStatus Status;
    QueueType Type;
    uint8_t HeadPosition;
    uint8_t TaiPositionl;
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="メソッド">
    
    // </editor-fold>

} Queue;

typedef enum  {
    ValueType,
    ReferenceType
} QueueType;

typedef enum{
    QueueIsIdle,
    QueueIsBusy,
}QueueStatus;

#define MAX_QUEUE_SIZE_DATA_TYPE 30
#define MAX_QUEUE_NUM_DATA_TYPE (MAX_QUEUE_SIZE_DATA_TYPE-1)



#define MAX_QUEUE_SIZE_ADD_TYPE 30
#define MAX_QUEUE_NUM_ADD_TYPE (MAX_QUEUE_SIZE_ADD_TYPE-1)

/******************************************************************************/

typedef struct {
    volatile unsigned int* IE_byte;
    uint8_t bit_num;
} queue_IE;

/******************************************************************************/

void init_queue(QueueType type,void* InputArray);
void enqueue_basic(QueueType type,void* InputArray, void* datas);
void* dequeue_basic(QueueType type, void* InputArray);

#endif

