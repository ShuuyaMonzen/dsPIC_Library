#include "EEPROM.h"

#define EEPROM_ADD 0
#ifndef EEPROM_READ_MODE
#define EEPROM_READ_MODE 1
#endif   

#ifndef EEPROM_WRITE_MODE
#define EEPROM_WRITE_MODE 0
#endif   

#define EEPROM_CHIP_ADDRESS  (0x50 | EEPROM_ADD)
#define EEPROM_CONTROL_BYTE (EEPROM_CHIP_ADDRESS << 1)

static uint16_t getEepromAdressBytes(uint8_t x, uint8_t y) {
    uint16_t tempAddressBytes = (x << 9) | (y << 3);
    tempAddressBytes = (x << 9) | (y << 3);
    return tempAddressBytes;
}

static uint8_t getWriteControlByte() {
    uint8_t controlByte = EEPROM_CONTROL_BYTE;
    controlByte &= (EEPROM_WRITE_MODE ^ 0xFE);
    return controlByte;
}

static uint8_t getReadControlByte() {
    uint8_t controlByte = EEPROM_CONTROL_BYTE;
    controlByte |= EEPROM_READ_MODE;
    return controlByte;
}

static void writeEeprom(dsPIC* dsPICObj,uint8_t x, uint8_t y, uint8_t* add, uint8_t length) {
    uint8_t i;
    uint16_t addressBytes = getEepromAdressBytes(x, y);
    uint8_t adressHiByte = ((uint8_t*) &addressBytes)[1];
    uint8_t adressLowByte = ((uint8_t*) &addressBytes)[0];
    uint8_t controlByte = getWriteControlByte();
    
    dsPICObj->startMI2C();
    while (!_MI2C1IF);
    dsPICObj->sendMI2C(controlByte);
    while (!_MI2C1IF);
    dsPICObj->sendMI2C(adressHiByte);
    while (!_MI2C1IF);
    dsPICObj->sendMI2C(adressLowByte);
    while (!_MI2C1IF);
    
    for (i = 0; i < length; i++) {
        dsPICObj->sendMI2C(add[i]);
        while (!_MI2C1IF);
    }

    dsPICObj->stopMI2C();
    while (!_MI2C1IF);
    __delay_ms(5);//書き込みサイクル
}

static void readEeprom(dsPIC* dsPICObj,uint8_t x, uint8_t y, uint8_t* add, uint8_t length) {
    uint8_t i;
    //getEepromAdressBytes(x, y);
    uint16_t addressBytes = getEepromAdressBytes(x, y);
    uint8_t adressHiByte = ((uint8_t*) &addressBytes)[1];
    uint8_t adressLowByte = ((uint8_t*) &addressBytes)[0];
    uint8_t controlByte = getWriteControlByte();
    
    dsPICObj->startMI2C();
    while (!_MI2C1IF);
    dsPICObj->sendMI2C(controlByte);
    while (!_MI2C1IF);
    dsPICObj->sendMI2C(adressHiByte);
    while (!_MI2C1IF);
    dsPICObj->sendMI2C(adressLowByte);
    while (!_MI2C1IF);

    dsPICObj->restartMI2C();
    while (!_MI2C1IF);

    controlByte = getReadControlByte();
    dsPICObj->sendMI2C(controlByte);
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
void writeEepromUint8(eepromStream* eepromStreamObj,uint8_t x, uint8_t y, uint8_t input_data) {
    writeEeprom(eepromStreamObj->dsPICObj, x, y, &input_data, 1);
}
void writeEepromInt8(eepromStream* eepromStreamObj,uint8_t x,uint8_t y,int8_t input_data){
    writeEeprom(eepromStreamObj->dsPICObj, x, y, (uint8_t*) &input_data, 1);
}

void writeEepromUint16(eepromStream* eepromStreamObj,uint8_t x, uint8_t y, uint16_t input_data) {
    writeEeprom(eepromStreamObj->dsPICObj, x, y, (uint8_t*) & input_data, 2);
}
void writeEepromInt16(eepromStream* eepromStreamObj,uint8_t x,uint8_t y,int16_t input_data){
    writeEeprom(eepromStreamObj->dsPICObj, x, y, (uint8_t*) & input_data, 2);
}

void writeEepromUint32(eepromStream* eepromStreamObj,uint8_t x, uint8_t y, uint32_t input_data) {
    writeEeprom(eepromStreamObj->dsPICObj, x, y, (uint8_t*) & input_data, 4);
}
void writeEepromInt32(eepromStream* eepromStreamObj,uint8_t x,uint8_t y,int32_t input_data){
    writeEeprom(eepromStreamObj->dsPICObj, x, y, (uint8_t*) & input_data, 4);
}

void writeEepromFloat(eepromStream* eepromStreamObj,uint8_t x, uint8_t y, float input_data) {
    writeEeprom(eepromStreamObj->dsPICObj, x, y, (uint8_t*) & input_data, 4);
}
/******************************************************************************/

/* << 読み込み >>*/
uint8_t readEepromUint8(eepromStream* eepromStreamObj,uint8_t x, uint8_t y) {
    uint8_t readData = 0;
    readEeprom(eepromStreamObj->dsPICObj, x, y, (uint8_t*)&readData, 1);
    return readData;
}
int8_t readEepromInt8(eepromStream* eepromStreamObj,uint8_t x,uint8_t y){
    int8_t readData = 0;
    readEeprom(eepromStreamObj->dsPICObj, x, y, (uint8_t*)&readData, 1);
    return readData;
}

uint16_t readEepromUint16(eepromStream* eepromStreamObj,uint8_t x, uint8_t y) {
    uint16_t readData = 0;
    readEeprom(eepromStreamObj->dsPICObj, x, y, (uint8_t*)&readData, 2);
    return readData;
}
int16_t readEepromInt16(eepromStream* eepromStreamObj,uint8_t x,uint8_t y){
    int16_t readData = 0;
    readEeprom(eepromStreamObj->dsPICObj, x, y, (uint8_t*)&readData, 2);
    return readData;
}

uint32_t readEepromUint32(eepromStream* eepromStreamObj,uint8_t x, uint8_t y) {
    uint32_t readData = 0;
    readEeprom(eepromStreamObj->dsPICObj, x, y, (uint8_t*)&readData, 4);
    return readData;
}
int32_t readEepromInt32(eepromStream* eepromStreamObj,uint8_t x,uint8_t y){
    int32_t readData = 0;
    readEeprom(eepromStreamObj->dsPICObj, x, y, (uint8_t*)&readData, 4);
    return readData;
}

float readEepromFloat(eepromStream* eepromStreamObj,uint8_t x, uint8_t y) {
    float readData = 0;
    readEeprom(eepromStreamObj->dsPICObj, x, y, (uint8_t*)&readData, 4);
    return readData;
}

eepromStream* newEeprom(dsPIC* dsPICObj){
    eepromStream* eepromStreamObj = (eepromStream*) malloc(sizeof (eepromStream));
    
    eepromStreamObj->dsPICObj = dsPICObj;
    eepromStreamObj->writeEepromUint8 = writeEepromUint8;
    eepromStreamObj->writeEepromInt8 = writeEepromInt8;
    eepromStreamObj->writeEepromUint16 = writeEepromUint16;
    eepromStreamObj->writeEepromInt16 = writeEepromInt16;
    eepromStreamObj->writeEepromUint32 = writeEepromUint32;
    eepromStreamObj->writeEepromInt32 = writeEepromInt32;
    eepromStreamObj->writeEepromFloat = writeEepromFloat;
    
    eepromStreamObj->readEepromUint8 = readEepromUint8;
    eepromStreamObj->readEepromInt8 = readEepromInt8;
    eepromStreamObj->readEepromUint16 = readEepromUint16;
    eepromStreamObj->readEepromInt16 = readEepromInt16;
    eepromStreamObj->readEepromUint32 = readEepromUint32;
    eepromStreamObj->readEepromInt32 = readEepromInt32;
    eepromStreamObj->readEepromFloat = readEepromFloat;
    
    return eepromStreamObj;
}