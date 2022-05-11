/* 
 * File:   Basic_lib_dsPIC.h
 * Author: 門前　秀弥
 *
 * Created on 2017/01/19, 22:06
 */
/*
    <README> 
 * 1:以下にある#defineに適切な数値またはピン名称を入れてください
 * <注意>
 * ピン名称について:RPxの形式で書いてください,モジュール自体を使用しない場合 not_used_module としてください(*I2CはPPSではありません)
 * 割り込み優先度について:0を割り込み優先度に設定した場合、割り込みは発生しません(*割り込みフラグは適切なタイミングでセットされます)
 * 
 * 2:まずmain関数の一番初めにsetup_dsPIC();を呼び出してください
 * 
 * 3:次に、setup_<モジュール名>();の関数を使うものだけ呼び出してください
 * 
 * 4:各モジュールの基本的な関数を自由につかってください。(関数の使い方は以下のプロトタイプ宣言の横に記述されています) 
 */

#ifndef BASIC_LIB_DSPIC_H
#define BASIC_LIB_DSPIC_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "Config_dsPIC33FJ128MC802.h"
#include "CodeConst_dsPIC33FJ128MC802.h"
#include <xc.h>
#include <libpic30.h>

typedef struct {
    // <editor-fold defaultstate="collapsed" desc="プロパティ">
    // <editor-fold defaultstate="collapsed" desc="UART">
    PPS UART1TX;
    PPS UART1RX;
    PPS UART2TX;
    PPS UART2RX;

    BaudRate UART1BaudRate;
    BaudRate UART2BaudRate;

    InterruptPriority UART1TxIP;
    InterruptPriority UART1RxIP;
    InterruptPriority UART1RxErrorIP;
    InterruptPriority UART2TxIP;
    InterruptPriority UART2RxIP;
    InterruptPriority UART2RxErrorIP;
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="OC">
    PPS OutputCompare1;
    PPS OutputCompare2;
    PPS OutputCompare3;
    PPS OutputCompare4;

    OC_Mode OC1And2Mode;
    OC_Mode OC3And4Mode;
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="QEI">
    PPS QEI1AInput;
    PPS QEI1BInput;
    PPS QEI2AInput;
    PPS QEI2BInput;

    InterruptPriority QEI1IP;
    InterruptPriority QEI2IP;
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="TMR">
    InterruptPriority TMR1IP;
    InterruptPriority TMR2IP;
    InterruptPriority TMR3IP;
    InterruptPriority TMR4IP;
    InterruptPriority TMR5IP;
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="MI2C">
    SystemClockI2C Fscl;
    InterruptPriority I2CM_IP;
    // </editor-fold>
    // </editor-fold>
} dsPicConfigValues;

typedef struct {
    // <editor-fold defaultstate="collapsed" desc="プロパティ">
    dsPicConfigValues* dsPicConfig;
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="メソッド">
    // <editor-fold defaultstate="collapsed" desc="UART">
    void (*sendUART1)(uint8_t byte);

    uint8_t(*recieveUART1)();

    void (*sendUART2)(uint8_t datas);

    uint8_t(*recieveUART2)();
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="I2C_Master">
    void (*startMI2C)();

    void (*sendMI2C)(uint8_t datas);

    uint8_t(*readMI2C)();

    void (*stopMI2C)();

    void (*rxOnMI2C)();

    void (*restartMI2C)();

    void (*sendAckMI2C)();

    void (*sendNackMI2C)();
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="OutPutCompare">
    void (*setDutyMicroSec)(OutputCompare ocNum, float microSec, ActiveDirection pinAction);

    void (*setDutyPercent)(OutputCompare ocNum, float percent, ActiveDirection pinAction);
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="Timer">
    void (*setDelay)(Timer timerNum, TimerMode mode, float sec, InterruptEnableEnum interruptEnable);
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="QEI">
    int16_t (*readQEI1)();

    int16_t (*readQEI2)();
    // </editor-fold>

    // </editor-fold>

} dsPIC;

/**
 * dsPIC初期設定関数
 * main関数で最初に呼び出してください
 */
dsPIC* dsPICInitialize();
#endif	/* BASIC_LIB_DSPIC_H */

