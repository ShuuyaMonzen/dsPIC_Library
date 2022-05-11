/* 
 * File:   Config_dsPIC33FJ128MC802.h
 * Author: clang
 *
 * Created on 2019/10/22, 21:07
 */

#ifndef CONFIG_DSPIC33FJ128MC802_H
#define CONFIG_DSPIC33FJ128MC802_H

#include "CodeConst_dsPIC33FJ128MC802.h"

// <editor-fold defaultstate="collapsed" desc="UART CONFIG">
/* ボーレート */
#define UART1_BAUD_RATE _9600bps
#define UART2_BAUD_RATE _9600bps
/*ピン配置*/
#define UART1_PIN_TX RP5
#define UART1_PIN_RX RP6
#define UART2_PIN_TX RP12
#define UART2_PIN_RX RP13
/*割り込み優先度*/
#define UART1TX_IP Disable
#define UART1RX_IP Disable
#define UART2TX_IP Disable
#define UART2RX_IP Disable
/*　<受信のエラー割込み>　*/
#define UART1RX_ERROR_IP (UART1RX_IP+1)
#define UART2RX_ERROR_IP (UART2RX_IP+1)
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="I2C CONFIG">
#define I2C_SYSTEM_CLOCK _400kHz
#define I2C_MASTER_IP Disable
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="OutputCompare CONFIG">
#define OC_1AND2_FREQUENCY DC_Motor
#define OC_3AND4_FREQUENCY ServoMotor
/*ピン配置*/
#define OC1_PIN NotUsedModule
#define OC2_PIN NotUsedModule
#define OC3_PIN NotUsedModule
#define OC4_PIN NotUsedModule
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="QEI CONFIG">
/*ピン配置*/
#define QEI1_PIN_A NotUsedModule
#define QEI1_PIN_B NotUsedModule
#define QEI2_PIN_A NotUsedModule
#define QEI2_PIN_B NotUsedModule
/*割り込み優先度*/
#define QEI1_IP Disable
#define QEI2_IP Disable
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="TMR CONFIG">
/*割り込み優先度*/
#define TMR1_IP Disable
#define TMR2_IP Disable
#define TMR3_IP Disable
#define TMR4_IP Disable
#define TMR5_IP Disable
// </editor-fold>

#endif	/* CONFIG_DSPIC33FJ128MC802_H */

