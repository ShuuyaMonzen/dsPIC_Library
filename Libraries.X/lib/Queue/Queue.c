#include "Queue.h"

void QueueInterruptOff(QueueInterrupt* queueInterruptObj) {
    if ((queueInterruptObj != NULL) || (queueInterruptObj->IE_BytePointer != NULL)) {
        *queueInterruptObj->IE_BytePointer = *queueInterruptObj->IE_BytePointer & ((1 << queueInterruptObj->bitNum)^0xFFFF);
    }
}

void QueueInterruptOn(QueueInterrupt* queueInterruptObj) {
    if ((queueInterruptObj != NULL) || (queueInterruptObj->IE_BytePointer != NULL)) {
        *queueInterruptObj->IE_BytePointer = *queueInterruptObj->IE_BytePointer | (1 << queueInterruptObj->bitNum);
    }
}

void InitQueue(Queue* queue) {
    uint8_t i = 0;
    queue->status = IsBusy_Queue; //アクセス禁止
    queue->headPosition = 0;
    queue->taiPosition = 0;
    if (queue->type == ValueType_Queue) {
        for (i = 0; i < MAX_DATA_TYPE_QUEUE_SIZE; i++) {
            queue->dataArrary[i] = 0;
        }
    } else if (queue->type == ReferenceType_Queue) {
        for (i = 0; i < MAX_ADDRESS_TYPE_QUEUE_SIZE; i++) {
            queue->addressArray[i] = NULL;
        }
    }
    queue->status = IsIdle_Queue;
}

void EnqueueBasic(Queue* queue, void* data) {
    while (queue->status == IsBusy_Queue);

    queue->status = IsBusy_Queue; //アクセス禁止
    if (queue->type == ValueType_Queue) {
        uint8_t* inputArray = (uint8_t*) data;
        uint8_t i = 0;
        for (i = 0; inputArray[i] != '\0'; i++) {
            queue->dataArrary[queue->taiPosition++] = inputArray[i];
            if (queue->taiPosition > MAX_DATA_TYPE_QUEUE_INDEX) {
                queue->taiPosition = 0;
            }
        }
    } else if (queue->type == ReferenceType_Queue) {
        queue->addressArray[queue->taiPosition++] = data;
        if (queue->taiPosition > MAX_ADDRESS_TYPE_QUEUE_INDEX) {
            queue->taiPosition = 0;
        }
    }
    queue->status = IsIdle_Queue;
}

void* DequeueBasic(Queue* queue) {
    static uint8_t returnValue = 0;
    void* returnAddress;
    while (queue->status == IsBusy_Queue);

    queue->status = IsBusy_Queue; //アクセス禁止
    if (queue->type == ValueType_Queue) {
        returnValue = queue->dataArrary[queue->headPosition++];
        if (queue->headPosition > MAX_DATA_TYPE_QUEUE_INDEX) {
            queue->headPosition = 0;
        }
        if ((queue->headPosition == queue->taiPosition) && (queue->taiPosition > 0)) {
            InitQueue(queue);
        }
        queue->status = IsIdle_Queue;
        return (void*) &returnValue;
    } else if (queue->type == ReferenceType_Queue) {
        returnAddress = queue->addressArray[queue->headPosition++];
        if (queue->headPosition > MAX_ADDRESS_TYPE_QUEUE_INDEX) {
            queue->headPosition = 0;
        }
        if ((queue->headPosition == queue->taiPosition) && (queue->taiPosition > 0)) {
            InitQueue(queue);
        }
        queue->status = IsIdle_Queue;
        return returnAddress;
    }
    return NULL;
}

// <editor-fold defaultstate="collapsed" desc="初期設定">
Queue* new_Queue(){
     Queue* queueObj = (Queue*) malloc(sizeof (Queue));
     queueObj->initQueue = InitQueue;
     queueObj->enqueueBasic = EnqueueBasic;
     queueObj->dequeueBasic = DequeueBasic;
     queueObj->queueInterruptOff = QueueInterruptOff;
     queueObj->queueInterruptOn = QueueInterruptOn;
     
     return queueObj;
}
// </editor-fold>
