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

void init_queue(enum ID_FIFO ID, void* InputArray) {

    if (ID == data) {
        basic_queue_data* temp_data;
        uint8_t i = 0;
        temp_data = (basic_queue_data*) InputArray;
        temp_data->access_control_data = writing_reading; //アクセス禁止
        temp_data->now_head = 0;
        temp_data->now_tail = 0;
        for (i = 0; i < MAX_QUEUE_SIZE_DATA_TYPE; i++) {
            temp_data->real_data[i] = 0;
        }
        temp_data->access_control_data = idle;
    } else if (ID == address) {
        basic_queue_add* temp_add = (basic_queue_add*) InputArray;
        uint8_t i = 0;
        temp_add->access_control_data = writing_reading; //アクセス禁止
        temp_add->now_head = 0;
        temp_add->now_tail = 0;
        for (i = 0; i < MAX_QUEUE_SIZE_ADD_TYPE; i++) {
            temp_add->real_data[i] = NULL;
        }
        temp_add->access_control_data = idle;
    }
}

void enqueue_basic(enum ID_FIFO ID, void* InputArray, void* datas) {
    if (ID == data) {
        basic_queue_data* temp_data = (basic_queue_data*) InputArray;
        uint8_t i = 0;
        uint8_t* datas_for_BQD= (uint8_t*) datas; //BQD=basic_queue_data
        
        for (i = 0; datas_for_BQD[i] != '\0'; i++) {
            while (temp_data->access_control_data != idle);
            if (temp_data->access_control_data == idle) {
                temp_data->access_control_data = writing_reading;
                temp_data->real_data[temp_data->now_tail++] = datas_for_BQD[i];
                if (temp_data->now_tail > MAX_QUEUE_NUM_DATA_TYPE) {
                    temp_data->now_tail = 0;
                }
                temp_data->access_control_data = idle;
            }
        }
    } else {
        basic_queue_add* temp_add = (basic_queue_add*) InputArray;
        //while (temp_add->access_control_data != idle);
        if (temp_add->access_control_data == idle) {
            temp_add->access_control_data = writing_reading;
            if (datas != NULL) {//NULLは入れない
                temp_add->real_data[temp_add->now_tail++] = datas;
            }
            if (temp_add->now_tail > MAX_QUEUE_NUM_ADD_TYPE) {
                temp_add->now_tail = 0;
            }
            temp_add->access_control_data = idle;
        }
    }
}

void* dequeue_basic(enum ID_FIFO ID, void* InputArray) {
    if (ID == data) {
        basic_queue_data* temp_data = (basic_queue_data*) InputArray;;
        static uint8_t return_data = 0;
        while (temp_data->access_control_data != idle);
        if (temp_data->access_control_data == idle) {
            temp_data->access_control_data = writing_reading;
            return_data = temp_data->real_data[temp_data->now_head++];
            if (temp_data->now_head > MAX_QUEUE_NUM_DATA_TYPE) {
                temp_data->now_head = 0;
            }

            temp_data->access_control_data = idle;
        }
        return (void*) &return_data;
    } else if (ID == address) {
        basic_queue_add* temp_add = (basic_queue_add*) InputArray;
        void* return_add = NULL;
        if (temp_add->access_control_data == idle) {
            temp_add->access_control_data = writing_reading;
            if (temp_add->real_data[temp_add->now_head] != NULL) {
                return_add = temp_add->real_data[temp_add->now_head++];
            }
            if (temp_add->now_head > MAX_QUEUE_NUM_ADD_TYPE) {
                temp_add->now_head = 0;
            }
            if ((temp_add->now_head == temp_add->now_tail) && (temp_add->now_tail > 0)) {
                init_queue(address, temp_add);
            }
            temp_add->access_control_data = idle;
        }
        return return_add;
    }
    return NULL;
}