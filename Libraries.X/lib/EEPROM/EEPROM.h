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
typedef struct eepromStream EepromStream;

struct eepromStream{
    dsPIC* dsPICObj;

    /* << 書き込み >>*/
    void (*writeEepromUint8)(EepromStream*, uint8_t, uint8_t, uint8_t);
    void (*writeEepromInt8)(EepromStream*, uint8_t, uint8_t, int8_t);
    void (*writeEepromUint16)(EepromStream*, uint8_t, uint8_t, uint16_t);
    void (*writeEepromInt16)(EepromStream*, uint8_t, uint8_t, int16_t);
    void (*writeEepromUint32)(EepromStream*, uint8_t, uint8_t, uint32_t);
    void (*writeEepromInt32)(EepromStream*, uint8_t, uint8_t, int32_t);
    void (*writeEepromFloat)(EepromStream*, uint8_t, uint8_t, float);

    /* << 読み込み >>*/
    uint8_t(*readEepromUint8)(EepromStream*, uint8_t, uint8_t);
    int8_t(*readEepromInt8)(EepromStream*, uint8_t, uint8_t);
    uint16_t(*readEepromUint16)(EepromStream*, uint8_t, uint8_t);
    int16_t(*readEepromInt16)(EepromStream*, uint8_t, uint8_t);
    uint32_t(*readEepromUint32)(EepromStream*, uint8_t, uint8_t);
    int32_t(*readEepromInt32)(EepromStream*, uint8_t, uint8_t);
    float (*readEepromFloat)(EepromStream*, uint8_t, uint8_t);
};

EepromStream* newEeprom();

#endif	/* EEPROM_H */

