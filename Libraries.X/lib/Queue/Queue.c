#include "Queue.h"

void queue_IE_OFF(queue_IE* TO_USE_QUEUE_IE) {
    if ((TO_USE_QUEUE_IE != NULL) || (TO_USE_QUEUE_IE->IE_byte != NULL)) {
        *TO_USE_QUEUE_IE->IE_byte = *TO_USE_QUEUE_IE->IE_byte & ((1 << TO_USE_QUEUE_IE->bit_num)^0xFFFF);
    }
}

void queue_IE_ON(queue_IE* TO_USE_QUEUE_IE) {
    if ((TO_USE_QUEUE_IE != NULL) || (TO_USE_QUEUE_IE->IE_byte != NULL)) {
        *TO_USE_QUEUE_IE->IE_byte = *TO_USE_QUEUE_IE->IE_byte | (1 << TO_USE_QUEUE_IE->bit_num);
    }
}

void initQueue(Queue* queue) {
    uint8_t i = 0;
    queue->Status = QueueIsBusy; //アクセス禁止
    queue->HeadPosition = 0;
    queue->TaiPositionl = 0;
    if (queue->Type == ValueType) {
        for (i = 0; i < MAX_QUEUE_SIZE_DATA_TYPE; i++) {
            queue->DataArrary[i] = 0;
        }
    } else if (queue->Type == ReferenceType) {
        for (i = 0; i < MAX_QUEUE_SIZE_ADD_TYPE; i++) {
            queue->AddressArray[i] = NULL;
        }
    }
    queue->Status = QueueIsIdle;
}

void enqueueBasic(Queue* queue, void* data) {
    while (queue->Status == QueueIsBusy);

    queue->Status = QueueIsBusy; //アクセス禁止
    if (queue->Type == ValueType) {
        uint8_t* inputArray = (uint8_t*) data;
        uint8_t i = 0;
        for (i = 0; inputArray[i] != '\0'; i++) {
            queue->DataArrary[queue->TaiPositionl++] = inputArray[i];
            if (queue->TaiPositionl > MAX_QUEUE_NUM_DATA_TYPE) {
                queue->TaiPositionl = 0;
            }
        }
    } else if (queue->Type == ReferenceType) {
        queue->AddressArray[queue->TaiPositionl++] = data;
        if (queue->TaiPositionl > MAX_QUEUE_NUM_ADD_TYPE) {
            queue->TaiPositionl = 0;
        }
    }
    queue->Status = QueueIsIdle;
}

void* dequeueBasic(Queue* queue) {
    static uint8_t returnValue = 0;
    void* returnAddress;
    while (queue->Status == QueueIsBusy);

    queue->Status = QueueIsBusy; //アクセス禁止
    if (queue->Type == ValueType) {
        returnValue = queue->DataArrary[queue->HeadPosition++];
        if (queue->HeadPosition > MAX_QUEUE_NUM_DATA_TYPE) {
            queue->HeadPosition = 0;
        }
        if ((queue->HeadPosition == queue->TaiPositionl) && (queue->TaiPositionl > 0)) {
            initQueue(queue);
        }
        queue->Status = QueueIsIdle;
        return (void*) &returnValue;
    } else if (queue->Type == ReferenceType) {
        returnAddress = queue->AddressArray[queue->HeadPosition++];
        if (queue->HeadPosition > MAX_QUEUE_NUM_ADD_TYPE) {
            queue->HeadPosition = 0;
        }
        if ((queue->HeadPosition == queue->TaiPositionl) && (queue->TaiPositionl > 0)) {
            initQueue(queue);
        }
        queue->Status = QueueIsIdle;
        return returnAddress;
    }
    return NULL;
}