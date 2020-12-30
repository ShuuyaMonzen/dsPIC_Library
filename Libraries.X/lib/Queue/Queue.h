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

// <editor-fold defaultstate="collapsed" desc="サイズ定義">
#define MAX_QUEUE_SIZE_DATA_TYPE 30
#define MAX_QUEUE_NUM_DATA_TYPE (MAX_QUEUE_SIZE_DATA_TYPE-1)

#define MAX_QUEUE_SIZE_ADD_TYPE 30
#define MAX_QUEUE_NUM_ADD_TYPE (MAX_QUEUE_SIZE_ADD_TYPE-1)
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="定数定義">
typedef enum  {
    ValueType,
    ReferenceType
} QueueType;

typedef enum{
    QueueIsIdle,
    QueueIsBusy,
}QueueStatus;
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="クラス定義">
typedef struct {
    // <editor-fold defaultstate="collapsed" desc="プロパティ">
    uint8_t DataArrary[MAX_QUEUE_SIZE_DATA_TYPE];
    void* AddressArray[MAX_QUEUE_SIZE_ADD_TYPE];
    
    QueueStatus Status;
    QueueType Type;
    uint8_t HeadPosition;
    uint8_t TaiPositionl;
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="メソッド">
    void (*init_queue)(QueueType type,void* InputArray);
    void  (*enqueue_basic)(QueueType type,void* InputArray, void* datas);
    void*  (*dequeue_basic)(QueueType type, void* InputArray);
    // </editor-fold>

} Queue;
// </editor-fold>

/******************************************************************************/

typedef struct {
    volatile unsigned int* IE_byte;
    uint8_t bit_num;
} queue_IE;

/******************************************************************************/

void initQueue(Queue* queue);
void enqueueBasic(Queue* queue, void* data);
void* dequeueBasic(Queue* queue);

#endif

