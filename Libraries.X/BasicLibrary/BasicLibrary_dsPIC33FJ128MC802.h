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
#include <stdio.h>
#include <math.h>
#include "Config_dsPIC33FJ128MC802.h"
#include "DefineValues_dsPIC33FJ128MC802.h"
#include <xc.h>
#include <libpic30.h>

/**
 * dsPIC初期設定関数
 * main関数で最初に呼び出してください
 */
void Initialize();

// <editor-fold defaultstate="collapsed" desc="UART">
void SendUART1(uint8_t byte);

uint8_t RecieveUART1();

void SendUART2(uint8_t datas);

uint8_t RecieveUART2();
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="I2C_Master">
void StartMI2C();

void SendMI2C(uint8_t datas);

uint8_t ReadMI2C();

void StopMI2C();

void RxOnMI2C();

void RestartMI2C();

void SendAckMI2C();

void SendNackMI2C();
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="OutPutCompare">
void SetDutyMicroSec(OutputCompare ocNum, float microSec, ActiveDirection pinAction);

void SetDutyPercent(OutputCompare ocNum, float percent, ActiveDirection pinAction);
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Timer">
void SetDelay(Timer timerNum, TimerMode mode, float sec, InterruptEnableEnum interruptEnable);
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="QEI">
int16_t ReadQEI1();

int16_t ReadQEI2();
// </editor-fold>
#endif	/* BASIC_LIB_DSPIC_H */

