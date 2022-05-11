#ifndef CODE_CONST_FOR_DSPIC33FJ128MC802_H
#define CODE_CONST_FOR_DSPIC33FJ128MC802_H

#include <stdint.h>

// <editor-fold defaultstate="collapsed" desc="Fcyc">
#ifndef Fcyc
#define Fcyc (80000000.0)//80MHz
#define Fosc Fcyc
#define FCY (40000000.0)//(Fcyc / 2.0)  40MHz
#endif
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="PPS">
typedef enum {
    RP0 = 0,
    RP1,
    RP2,
    RP3,
    RP4,
    RP5,
    RP6,
    RP7,
    RP8,
    RP9,
    RP10,
    RP11,
    RP12,
    RP13,
    RP14,
    RP15,
    NotUsedModule = 200
} PPS;
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="共通">

typedef enum {
    ActiveHigh,
    ActiveLow
} ActiveDirection;

typedef enum {
    Disable = 0,
    _1,
    _2,
    _3,
    _4,
    _5,
    _6,
    _7
} InterruptPriority;

typedef enum {
    InterruptEnable,
    InterruptDisable
} InterruptEnableEnum;
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Timer">

typedef enum {
    Timer1,
    Timer2,
    Timer3,
    Timer4,
    Timer5
} Timer;

typedef enum {
    MilliSecond,
    MicroSecond,
    NanoSecond
} TimerMode;
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="OutputCompare">
typedef enum {
    OutputCompare1,
    OutputCompare2,
    OutputCompare3,
    OutputCompare4
} OutputCompare;

typedef enum {
    ServoMotor,
    DC_Motor
} OC_Mode;
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="UART">
typedef enum {
    _9600bps,
    _19200bps,
    _57600bps,
    _115200bps
} BaudRate;
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="I2C">
typedef enum {
    NotUse,
    _100kHz,
    _400kHz,
    _1MHz
} SystemClockI2C;

typedef enum {
    ReadMode,
    WriteMode
} EEPROM_Mode;
// </editor-fold>

#endif	/* CODE_CONST_FOR_DSPIC33FJ128MC802_H */

