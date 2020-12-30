/* 
 * File:   EEPROM.h
 * Author: Shuuya
 *
 * Created on 2017/02/18, 19:31
 */

#ifndef EEPROM_H
#define EEPROM_H


#include "../BasicLibrary/BasicLibrary_dsPIC33FJ128MC802.h"

#define EEPROM_ADD 0
#ifndef EEPROM_READ_MODE
#define EEPROM_READ_MODE 1
#endif   

#ifndef EEPROM_WRITE_MODE
#define EEPROM_WRITE_MODE 0
#endif   

    /* <注意事項>*/
    // 24LC256もしくは互換品の使用を前提
    // x(min) = 0,x(max)=31 ,y(min) = 0,y(max)=31
    // (x,y)の領域は4Byte(float分)

    /* << 書き込み >>*/
    void write_EEPROM_uint8(dsPIC* dsPICObj, uint8_t x, uint8_t y, uint8_t input_data);
    void write_EEPROM_int8(dsPIC* dsPICObj, uint8_t x, uint8_t y, int8_t input_data);
    void write_EEPROM_uint16(dsPIC* dsPICObj, uint8_t x, uint8_t y, uint16_t input_data);
    void write_EEPROM_int16(dsPIC* dsPICObj, uint8_t x, uint8_t y, int16_t input_data);
    void write_EEPROM_uint32(dsPIC* dsPICObj, uint8_t x, uint8_t y, uint32_t input_data);
    void write_EEPROM_int32(dsPIC* dsPICObj, uint8_t x, uint8_t y, int32_t input_data);
    void write_EEPROM_float(dsPIC* dsPICObj, uint8_t x, uint8_t y, float input_data);

    /* << 読み込み >>*/
    void read_EEPROM_uint8(dsPIC* dsPICObj, uint8_t x, uint8_t y, uint8_t* output_data);
    void read_EEPROM_int8(dsPIC* dsPICObj, uint8_t x, uint8_t y, int8_t* output_data);
    void read_EEPROM_uint16(dsPIC* dsPICObj, uint8_t x, uint8_t y, uint16_t* output_data);
    void read_EEPROM_int16(dsPIC* dsPICObj, uint8_t x, uint8_t y, int16_t* output_data);
    void read_EEPROM_uint32(dsPIC* dsPICObj, uint8_t x, uint8_t y, uint32_t* output_data);
    void read_EEPROM_int32(dsPIC* dsPICObj, uint8_t x, uint8_t y, int32_t* output_data);
    void read_EEPROM_float(dsPIC* dsPICObj, uint8_t x, uint8_t y, float* output_data);

#endif	/* EEPROM_H */

