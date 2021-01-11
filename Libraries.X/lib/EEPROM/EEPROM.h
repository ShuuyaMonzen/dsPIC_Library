/* 
 * File:   EEPROM.h
 * Author: Shuuya
 *
 * Created on 2017/02/18, 19:31
 */

#ifndef EEPROM_H
#define EEPROM_H


#include "../BasicLibrary/BasicLibrary_dsPIC33FJ128MC802.h"

/* <注意事項>*/
// 24LC256もしくは互換品の使用を前提
// x(min) = 0,x(max)=31 ,y(min) = 0,y(max)=31
// (x,y)の領域は4Byte(float分)
typedef struct eepromStream;

typedef struct {
    dsPIC* dsPICObj;

    /* << 書き込み >>*/
    void (*writeEepromUint8)(void* eepromStreamObj, uint8_t x, uint8_t y, uint8_t input_data);
    void (*writeEepromInt8)(void* eepromStreamObj, uint8_t x, uint8_t y, int8_t input_data);
    void (*writeEepromUint16)(void* eepromStreamObj, uint8_t x, uint8_t y, uint16_t input_data);
    void (*writeEepromInt16)(void* eepromStreamObj, uint8_t x, uint8_t y, int16_t input_data);
    void (*writeEepromUint32)(void* eepromStreamObj, uint8_t x, uint8_t y, uint32_t input_data);
    void (*writeEepromInt32)(void* eepromStreamObj, uint8_t x, uint8_t y, int32_t input_data);
    void (*writeEepromFloat)(void* eepromStreamObj, uint8_t x, uint8_t y, float input_data);

    /* << 読み込み >>*/
    uint8_t(*readEepromUint8)(void* eepromStreamObj, uint8_t x, uint8_t y);
    int8_t(*readEepromInt8)(void* eepromStreamObj, uint8_t x, uint8_t y);
    uint16_t(*readEepromUint16)(void* eepromStreamObj, uint8_t x, uint8_t y);
    int16_t(*readEepromInt16)(void* eepromStreamObj, uint8_t x, uint8_t y);
    uint32_t(*readEepromUint32)(void* eepromStreamObj, uint8_t x, uint8_t y);
    int32_t(*readEepromInt32)(void* eepromStreamObj, uint8_t x, uint8_t y);
    float (*readEepromFloat)(void* eepromStreamObj, uint8_t x, uint8_t y);
} eepromStream;

eepromStream* newEeprom();

#endif	/* EEPROM_H */

