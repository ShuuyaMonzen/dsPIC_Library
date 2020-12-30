#include "EEPROM.h"

#define EEPROM_CHIP_ADDRESS  (0x50 | EEPROM_ADD)
#define EEPROM_CONTROL_BYTE (EEPROM_CHIP_ADDRESS << 1)

static uint8_t hi_adress;
static uint8_t low_adress;
static uint8_t control_byte = EEPROM_CONTROL_BYTE;

static void set_adress(uint8_t x, uint8_t y) {
    uint16_t temp_add = 0;
    temp_add = (x << 9) | (y << 3);
    hi_adress = ((uint8_t*) & temp_add)[1];
    low_adress = ((uint8_t*) & temp_add)[0];
}

static void set_write_Control_byte() {
    control_byte = EEPROM_CONTROL_BYTE;
    control_byte &= (EEPROM_WRITE_MODE ^ 0xFE);
}

static void set_read_Control_byte() {
    control_byte = EEPROM_CONTROL_BYTE;
    control_byte |= EEPROM_READ_MODE;
}

static void write_EEPROM(dsPIC* dsPICObj,uint8_t x, uint8_t y, uint8_t* add, uint8_t length) {
    uint8_t i;
    set_adress(x, y);
    set_write_Control_byte();
    
    dsPICObj->startMI2C();
    while (!_MI2C1IF);
    dsPICObj->sendMI2C(control_byte);
    while (!_MI2C1IF);
    dsPICObj->sendMI2C(hi_adress);
    while (!_MI2C1IF);
    dsPICObj->sendMI2C(low_adress);
    while (!_MI2C1IF);
    
    for (i = 0; i < length; i++) {
        dsPICObj->sendMI2C(add[i]);
        while (!_MI2C1IF);
    }

    dsPICObj->stopMI2C();
    while (!_MI2C1IF);
    __delay_ms(5);//書き込みサイクル
}

static void read_EEPROM(dsPIC* dsPICObj,uint8_t x, uint8_t y, uint8_t* add, uint8_t length) {
    uint8_t i;
    set_adress(x, y);
    set_write_Control_byte();
    
    dsPICObj->startMI2C();
    while (!_MI2C1IF);
    dsPICObj->sendMI2C(control_byte);
    while (!_MI2C1IF);
    dsPICObj->sendMI2C(hi_adress);
    while (!_MI2C1IF);
    dsPICObj->sendMI2C(low_adress);
    while (!_MI2C1IF);

    dsPICObj->restartMI2C();
    while (!_MI2C1IF);

    set_read_Control_byte();
    dsPICObj->sendMI2C(control_byte);
    while (!_MI2C1IF);
    dsPICObj->rxOnMI2C();

    for (i = 0; i < length; i++) {
        while (!_MI2C1IF);
        add[i] = dsPICObj->readMI2C();
        if (i == (length - 1)) {//最後の1回
            dsPICObj->sendNackMI2C();
            while (!_MI2C1IF);
        } else {
            dsPICObj->sendAckMI2C();
            while (!_MI2C1IF);
            dsPICObj->rxOnMI2C();
        }
    }
    dsPICObj->stopMI2C();
    while (!_MI2C1IF);
}

/* << 書き込み >>*/
void write_EEPROM_uint8(dsPIC* dsPICObj,uint8_t x, uint8_t y, uint8_t input_data) {
    write_EEPROM(dsPICObj, x, y, &input_data, 1);
}
void write_EEPROM_int8(dsPIC* dsPICObj,uint8_t x,uint8_t y,int8_t input_data){
    write_EEPROM(dsPICObj, x, y, (uint8_t*) &input_data, 1);
}

void write_EEPROM_uint16(dsPIC* dsPICObj,uint8_t x, uint8_t y, uint16_t input_data) {
    write_EEPROM(dsPICObj, x, y, (uint8_t*) & input_data, 2);
}
void write_EEPROM_int16(dsPIC* dsPICObj,uint8_t x,uint8_t y,int16_t input_data){
    write_EEPROM(dsPICObj, x, y, (uint8_t*) & input_data, 2);
}

void write_EEPROM_uint32(dsPIC* dsPICObj,uint8_t x, uint8_t y, uint32_t input_data) {
    write_EEPROM(dsPICObj, x, y, (uint8_t*) & input_data, 4);
}
void write_EEPROM_int32(dsPIC* dsPICObj,uint8_t x,uint8_t y,int32_t input_data){
    write_EEPROM(dsPICObj, x, y, (uint8_t*) & input_data, 4);
}

void write_EEPROM_float(dsPIC* dsPICObj,uint8_t x, uint8_t y, float input_data) {
    write_EEPROM(dsPICObj, x, y, (uint8_t*) & input_data, 4);
}
/******************************************************************************/

/* << 読み込み >>*/
void read_EEPROM_uint8(dsPIC* dsPICObj,uint8_t x, uint8_t y, uint8_t* output_data) {
    read_EEPROM(dsPICObj, x, y, (uint8_t*) output_data, 1);
}
void read_EEPROM_int8(dsPIC* dsPICObj,uint8_t x,uint8_t y,int8_t* output_data){
    read_EEPROM(dsPICObj, x, y, (uint8_t*)output_data, 1);
}

void read_EEPROM_uint16(dsPIC* dsPICObj,uint8_t x, uint8_t y, uint16_t* output_data) {
    read_EEPROM(dsPICObj, x, y, (uint8_t*) output_data, 2);
}
void read_EEPROM_int16(dsPIC* dsPICObj,uint8_t x,uint8_t y,int16_t* output_data){
    read_EEPROM(dsPICObj, x, y, (uint8_t*) output_data, 2);
}

void read_EEPROM_uint32(dsPIC* dsPICObj,uint8_t x, uint8_t y, uint32_t* output_data) {
    read_EEPROM(dsPICObj, x, y, (uint8_t*) output_data, 4);
}
void read_EEPROM_int32(dsPIC* dsPICObj,uint8_t x,uint8_t y,int32_t* output_data){
    read_EEPROM(dsPICObj, x, y, (uint8_t*) output_data, 4);
}

void read_EEPROM_float(dsPIC* dsPICObj,uint8_t x, uint8_t y, float* output_data) {
    read_EEPROM(dsPICObj, x, y, (uint8_t*) output_data, 4);
}