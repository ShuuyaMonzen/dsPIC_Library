#include "BasicLibrary_dsPIC33FJ128MC802.h"

static float T2CKPS = 1.0;
static float T3CKPS = 1.0;

// <editor-fold defaultstate="collapsed" desc="pragma">
// FBS
#pragma config BWRP = WRPROTECT_OFF     // Boot Segment Write Protect (Boot Segment may be written)
#pragma config BSS = NO_FLASH           // Boot Segment Program Flash Code Protection (No Boot program Flash segment)
#pragma config RBS = NO_RAM             // Boot Segment RAM Protection (No Boot RAM)

// FSS
#pragma config SWRP = WRPROTECT_OFF     // Secure Segment Program Write Protect (Secure segment may be written)
#pragma config SSS = NO_FLASH           // Secure Segment Program Flash Code Protection (No Secure Segment)
#pragma config RSS = NO_RAM             // Secure Segment Data RAM Protection (No Secure RAM)

// FGS
#pragma config GWRP = OFF               // General Code Segment Write Protect (User program memory is not write-protected)
#pragma config GSS = OFF                // General Segment Code Protection (User program memory is not code-protected)

// FOSCSEL
#pragma config FNOSC = FRC              // Oscillator Mode (Internal Fast RC (FRC))
#pragma config IESO = ON                // Internal External Switch Over Mode (Start-up device with FRC, then automatically switch to user-selected oscillator source when ready)

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Source (Primary Oscillator Disabled)
#pragma config OSCIOFNC = ON            // OSC2 Pin Function (OSC2 pin has digital I/O function)
#pragma config IOL1WAY = OFF            // Peripheral Pin Select Configuration (Allow Multiple Re-configurations)
#pragma config FCKSM = CSECMD           // Clock Switching and Monitor (Clock switching is enabled, Fail-Safe Clock Monitor is disabled)

// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler (1:32,768)
#pragma config WDTPRE = PR128           // WDT Prescaler (1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog timer enabled/disabled by user software)

// FPOR
#pragma config FPWRT = PWR128           // POR Timer Value (128ms)
#pragma config ALTI2C = OFF             // Alternate I2C  pins (I2C mapped to SDA1/SCL1 pins)
#pragma config LPOL = OFF               // Motor Control PWM Low Side Polarity bit (PWM module low side output pins have active-low output polarity)
#pragma config HPOL = OFF               // Motor Control PWM High Side Polarity bit (PWM module high side output pins have active-low output polarity)
#pragma config PWMPIN = ON             // Motor Control PWM Module Pin Mode bit (PWM module pins controlled by PWM module at device Reset)

// FICD
#pragma config ICS = PGD1               // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)
// </editor-fold>

typedef struct {
    uint8_t BunshuHi;
    float microSec;
    uint16_t real_data;
} OutPutCompareSettingValues;
static OutPutCompareSettingValues _changeBeforeOC[5] = {};

typedef struct {
    uint8_t TkcpsValue;
    TimerMode Mode;
    float Sec;
    uint16_t real_data;
} TimerSettingValues;
static TimerSettingValues _changeBeforeTMR[5] = {};

#define PR_MAX_VAL  (65535.0)

float GetBaudRate(BaudRate br) {
    switch (br) {
        case _9600bps:
            return 9600.0;
        case _19200bps:
            return 19200.0;
        case _57600bps:
            return 57600.0;
        case _115200bps:
            return 115200.0;
        default:
            return 0;
    }
}

float GetI2C_SystemClock(SystemClockI2C sc) {
    switch (sc) {
        case _100kHz:
            return 100000.0;
        case _400kHz:
            return 400000.0;
        case _1MHz:
            return 1000000.0;
        default:
            return 0;
    }
}

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

// <editor-fold defaultstate="collapsed" desc="初期設定">

static void Setup_dsPIC() {
    OSCTUN = 18;
    CLKDIVbits.FRCDIV = 0;
    CLKDIVbits.PLLPRE = 0;
    PLLFBD = 40 - 2;
    CLKDIVbits.PLLPOST = 0;
    RCONbits.SWDTEN = 0;
    __builtin_write_OSCCONH(0x01);
    __builtin_write_OSCCONL(0x01);
    while (OSCCONbits.COSC != 0b001);
    while (OSCCONbits.LOCK == 0);
    AD1PCFGL = 0xFFFF; //全てデジタルピンへ
    TRISA = 0;
    LATA = 0;
    CORCONbits.IPL3 = 0;
    SRbits.IPL = 0;
    INTCON1bits.NSTDIS = 0;
    INTCON2bits.ALTIVT = 0;
    //PLLを起動、安定まで待つ
    //80MHz
}

static void SetConfigValues(dsPicConfigValues* config) {
    config->UART1BaudRate = UART1_BAUD_RATE;
    config->UART1TxIP = UART1TX_IP;
    config->UART1RxIP = UART1RX_IP;

    config->UART2BaudRate = UART2_BAUD_RATE;
    config->UART2TxIP = UART2TX_IP;
    config->UART2RxIP = UART2RX_IP;
}

static void SetupPPS(dsPicConfigValues* dsPIC_Object) {
    volatile uint8_t* pointer = &(((volatile uint8_t*) & RPOR0)[0]);
    uint16_t process = 0;

    TRISB = 0xFFFF;

    // <editor-fold defaultstate="collapsed" desc="UART1">
    if (dsPIC_Object->UART1TX != NotUsedModule) {
        TRISB = (TRISB & ((1 << dsPIC_Object->UART1TX) ^ 0xFFFF));
        pointer[dsPIC_Object->UART1TX] = 3;
    }

    if (dsPIC_Object->UART1RX != NotUsedModule) {
        TRISB = (TRISB | (1 << dsPIC_Object->UART1RX));
        RPINR18bits.U1RXR = dsPIC_Object->UART1RX;
        process = process | (1 << dsPIC_Object->UART1RX);
    }
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="UART2">
    if (dsPIC_Object->UART2TX != NotUsedModule) {
        TRISB = (TRISB & ((1 << dsPIC_Object->UART2TX) ^ 0xFFFF));
        pointer[dsPIC_Object->UART2TX] = 5;
    }

    if (dsPIC_Object->UART2RX != NotUsedModule) {
        TRISB = (TRISB | (1 << dsPIC_Object->UART2RX));
        RPINR19bits.U2RXR = dsPIC_Object->UART2RX;
        process = process | (1 << dsPIC_Object->UART2RX);
    }
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="OC1">
    if (dsPIC_Object->OutputCompare1 != NotUsedModule) {
        TRISB = (TRISB & ((1 << dsPIC_Object->OutputCompare1) ^ 0xFFFF)); //ピン設定
        pointer[dsPIC_Object->OutputCompare1] = 0x12; //ピン設定
    }
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="OC2">
    if (dsPIC_Object->OutputCompare2 != NotUsedModule) {
        TRISB = (TRISB & ((1 << dsPIC_Object->OutputCompare2) ^ 0xFFFF)); //ピン設定
        pointer[dsPIC_Object->OutputCompare2] = 0x13; //ピン設定
    }
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="OC3">
    if (dsPIC_Object->OutputCompare3 != NotUsedModule) {
        TRISB = (TRISB & ((1 << dsPIC_Object->OutputCompare3) ^ 0xFFFF)); //ピン設定
        pointer[dsPIC_Object->OutputCompare3] = 0x14; //ピン設定
    }
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="OC4">
    if (dsPIC_Object->OutputCompare4 != NotUsedModule) {
        TRISB = (TRISB & ((1 << dsPIC_Object->OutputCompare4) ^ 0xFFFF)); //ピン設定
        pointer[dsPIC_Object->OutputCompare4] = 0x15; //ピン設定
    }
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="QEI1">
    if ((dsPIC_Object->QEI1AInput != NotUsedModule) &&
            (dsPIC_Object->QEI1BInput != NotUsedModule)) {
        TRISB = (TRISB | (1 << dsPIC_Object->QEI1AInput));
        RPINR14bits.QEA1R = dsPIC_Object->QEI1AInput;
        process = process | (1 << dsPIC_Object->QEI1AInput);
        TRISB = (TRISB | (1 << dsPIC_Object->QEI1BInput));
        RPINR14bits.QEB1R = dsPIC_Object->QEI1BInput;
        process = process | (1 << dsPIC_Object->QEI1BInput);
    }
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="QEI2">
    if ((dsPIC_Object->QEI2AInput != NotUsedModule) &&
            (dsPIC_Object->QEI2BInput != NotUsedModule)) {
        TRISB = (volatile unsigned int) (TRISB | (1 << dsPIC_Object->QEI2AInput));
        RPINR16bits.QEA2R = dsPIC_Object->QEI2AInput;
        process = process | (1 << dsPIC_Object->QEI2AInput);
        TRISB = (TRISB | (1 << dsPIC_Object->QEI2BInput));
        RPINR16bits.QEB2R = dsPIC_Object->QEI2BInput;
        process = process | (1 << dsPIC_Object->QEI2BInput);
    }
    // </editor-fold>
    TRISB = TRISB & process;
    __delay_ms(10);
}

static void SetupUART(dsPicConfigValues* dsPIC_Object) {

    if (dsPIC_Object->UART1TX != NotUsedModule ||
            dsPIC_Object->UART1RX != NotUsedModule) {
        U1MODE = 0;
        U1STA = 0;
        U1BRG = 0;
        U1MODEbits.BRGH = 1;
        PMD1bits.U1MD = 0;
        float uart1BaudRate = GetBaudRate(dsPIC_Object->UART1BaudRate);
        U1BRG = ((((float) FCY) / ((float) uart1BaudRate * 4.0)) - 1.0);

        U1MODEbits.PDSEL = 0;
        U1MODEbits.STSEL = 0;

        _U1TXIF = 0;
        if (dsPIC_Object->UART1TxIP == Disable) {
            _U1TXIE = 0;
        } else {
            _U1TXIE = 1;
        }
        _U1TXIP = dsPIC_Object->UART1TxIP;

        _U1RXIF = 0;
        if (dsPIC_Object->UART1RxIP == Disable) {
            _U1RXIE = 0;
        } else {
            _U1RXIE = 1;
        }
        _U1RXIP = dsPIC_Object->UART1RxIP;

        _U1EIF = 0;
        if (dsPIC_Object->UART1RxErrorIP == Disable) {
            _U1EIE = 0;
        } else {
            _U1EIE = 1;
        }
        _U1EIP = dsPIC_Object->UART1RxErrorIP;

        U1MODEbits.RTSMD = 0;
        U1STAbits.UTXISEL0 = 1;
        U1STAbits.UTXISEL1 = 0;

        U1MODEbits.UARTEN = 1;
        U1STAbits.UTXEN = 1;
        U1MODEbits.UEN = 0; //TX1,RX1
    }
    if (dsPIC_Object->UART2TX != NotUsedModule ||
            dsPIC_Object->UART2RX != NotUsedModule) {
        U2MODE = 0;
        U2STA = 0;
        U2BRG = 0;

        U2MODEbits.BRGH = 1; //1:高速モード
        PMD1bits.U2MD = 0;
        float uart2BaudRate = GetBaudRate(dsPIC_Object->UART2BaudRate);
        U2BRG = ((((float) FCY) / ((float) uart2BaudRate * 4.0)) - 1.0);
        U2MODEbits.PDSEL = 0;
        U2MODEbits.STSEL = 0;

        _U2TXIF = 0;
        if (dsPIC_Object->UART2TxIP == Disable) {
            _U2TXIE = 0;
        } else {
            _U2TXIE = 1;
        }
        _U2TXIP = dsPIC_Object->UART2TxIP;

        _U2RXIF = 0;
        if (dsPIC_Object->UART2RxIP == Disable) {
            _U2RXIE = 0;
        } else {
            _U2RXIE = 1;
        }
        _U2RXIP = dsPIC_Object->UART2RxIP;

        _U2EIF = 0;
        if (dsPIC_Object->UART2RxErrorIP == Disable) {
            _U2EIE = 0;
        } else {
            _U2EIE = 1;
        }
        _U2EIP = dsPIC_Object->UART2RxErrorIP;

        U2MODEbits.RTSMD = 0;
        U2STAbits.UTXISEL0 = 0;
        U2STAbits.UTXISEL1 = 0;

        U2MODEbits.UARTEN = 1;
        U2STAbits.UTXEN = 1;
        U2MODEbits.UEN = 0; //TX2,RX2
    }
    __delay_ms(1);
}

static void SetupMI2C(dsPicConfigValues* dsPIC_Object) {
    if (dsPIC_Object->Fscl != NotUse) {
        float fscl = GetI2C_SystemClock(dsPIC_Object->Fscl);
        float I2C_BAUD = (((((1.0 / fscl) - (130.0 / 1000000000.0)) * ((float) FCY))) - 2);

        _TRISB8 = 1;
        _TRISB9 = 1;

        I2C1CON = 0;
        I2C1STAT = 0;
        _I2C1MD = 0;
        I2C1MSK = 0;
        I2C1ADD = 0;

        I2C1BRG = I2C_BAUD;
        _MI2C1IF = 0;
        if (dsPIC_Object->I2CM_IP == Disable) {
            _MI2C1IE = 0;
        } else {
            _MI2C1IE = 1;
        }
        _MI2C1IP = dsPIC_Object->I2CM_IP;

        _SI2C1IF = 0;
        _SI2C1IE = 0;
        _SI2C1IP = 0;

        _I2CEN = 1;
        __delay_ms(1);
    }
}

static uint16_t GetBunshuhi(float periodMilliSec) {
    float PR_RegisterValue = 0;
    float Bunshuhi = 0;
    uint8_t i;
    for (i = 0; i < 4; i++) {
        Bunshuhi = pow(8.0, i);
        if (Bunshuhi > 64.0) {
            Bunshuhi = 256.0;
        }
        PR_RegisterValue = (((periodMilliSec) * FCY) / (Bunshuhi));
        if (PR_RegisterValue <= PR_MAX_VAL) {
            break;
        } else if (i == 3) {
            //ToDo 例外処理
            break;
        }
    }
    return Bunshuhi;
}

static void SetupOC(dsPicConfigValues* dsPIC_Object) {
    float TCKPS, temp;
    float OC1And2Period, OC3And4Period;
    uint8_t i;

    if ((dsPIC_Object->OutputCompare1 != NotUsedModule) ||
            (dsPIC_Object->OutputCompare2 != NotUsedModule)) {

        //ToDo Enumから値取得
        if (dsPIC_Object->OC1And2Mode == ServoMotor) {
            OC1And2Period = (20e-3); //20ms
        } else {
            OC1And2Period = (100e-9); //10kHz→100ns
        }
        OC1R = 0;
        OC1RS = 0;
        OC1CON = 0;
        OC2R = 0;
        OC2RS = 0;
        OC2CON = 0;
        T2CON = 0;
        PR2 = 0xFFFF;


        T2CONbits.TCKPS = i;
        //T2CKPS = TCKPS;
        if (dsPIC_Object->OutputCompare1 != NotUsedModule) {
            _OC1MD = 0;
            OC1CONbits.OCM = 6;
            OC1CONbits.OCTSEL = 0;
            T2CONbits.TON = 1;
        }

        if (dsPIC_Object->OutputCompare2 != NotUsedModule) {
            _OC2MD = 0;
            OC2CONbits.OCM = 6;
            OC2CONbits.OCTSEL = 0;
            T2CONbits.TON = 1;
        }
    }
    if ((dsPIC_Object->OutputCompare3 != NotUsedModule) ||
            (dsPIC_Object->OutputCompare4 != NotUsedModule)) {
        if (dsPIC_Object->OC3And4Mode == ServoMotor) {
            OC3And4Period = (20e-3); //20ms
        } else {
            OC3And4Period = (100e-9); //10kHz
        }
        OC3R = 0;
        OC3RS = 0;
        OC3CON = 0;
        OC4R = 0;
        OC4RS = 0;
        OC4CON = 0;
        T3CON = 0;
        for (i = 0; i < 4; i++) {
            TCKPS = pow(8.0, i);
            if (TCKPS > 64.0) {
                TCKPS = 256.0;
            }

            temp = ((OC3And4Period) * FCY) / (TCKPS);
            if (temp <= PR_MAX_VAL) {
                PR3 = temp;
                break;
            } else if (i == 3) {
                PR3 = 0xFFFF;
            }
        }
        T3CONbits.TCKPS = i;
        //T3CKPS = TCKPS;
        if (dsPIC_Object->OutputCompare3 != NotUsedModule) {
            _OC3MD = 0;
            OC3CONbits.OCM = 6;
            OC3CONbits.OCTSEL = 1; //1:TMR3をタイマーベースとする
            T3CONbits.TON = 1;
        }
        if (dsPIC_Object->OutputCompare4 != NotUsedModule) {
            _OC4MD = 0;
            OC4CONbits.OCM = 6;
            OC4CONbits.OCTSEL = 1;
            T3CONbits.TON = 1;
        }
    }
}

static void SetupQEI(dsPicConfigValues* dsPIC_Object) {
    if ((dsPIC_Object->QEI1AInput != NotUsedModule) &&
            (dsPIC_Object->QEI1BInput != NotUsedModule)) {
        _QEI1IF = 0;
        if (dsPIC_Object->QEI1IP == Disable) {
            _QEI1IE = 0;
        } else {
            _QEI1IE = 1;
        }
        _QEI1IP = dsPIC_Object->QEI1IP;
        POS1CNT = 0x7FFF;
        MAX1CNT = 0xFFFF; // +32767 ~ -32767, +32767のときリセット
        QEI1CON = 0;
        _QEI1MD = 0;
        QEI1CONbits.QEIM = 7;
        QEI1CONbits.PCDOUT = 0;
    }
    if ((dsPIC_Object->QEI2AInput != NotUsedModule) &&
            (dsPIC_Object->QEI2BInput != NotUsedModule)) {
        _QEI2IF = 0;
        if (dsPIC_Object->QEI2IP == Disable) {
            _QEI2IE = 0;
        } else {
            _QEI2IE = 1;
        }
        _QEI2IP = dsPIC_Object->QEI2IP;
        POS2CNT = 0x7FFF;
        MAX2CNT = 0xFFFF;
        QEI2CON = 0;
        _QEI2MD = 0;
        QEI2CONbits.QEIM = 7;
        QEI2CONbits.PCDOUT = 0;
    }
}

static void SetupTMR(dsPicConfigValues* dsPIC_Object) {
    _T1IF = 0;
    if (dsPIC_Object->TMR1IP == Disable) {
        _T1IE = 0;
    } else {
        _T1IE = 1;
    }
    _T1IP = dsPIC_Object->TMR1IP;

    _T2IF = 0;
    if (dsPIC_Object->TMR2IP == Disable) {
        _T2IE = 0;
    } else {
        _T2IE = 1;
    }
    _T2IP = dsPIC_Object->TMR2IP;

    _T3IF = 0;
    if (dsPIC_Object->TMR3IP == Disable) {
        _T3IE = 0;
    } else {
        _T3IE = 1;
    }
    _T3IP = dsPIC_Object->TMR3IP;

    _T4IF = 0;
    if (dsPIC_Object->TMR4IP == Disable) {
        _T4IE = 0;
    } else {
        _T4IE = 1;
    }
    _T4IP = dsPIC_Object->TMR4IP;

    _T5IF = 0;
    if (dsPIC_Object->TMR5IP == Disable) {
        _T5IE = 0;
    } else {
        _T5IE = 1;
    }
    _T5IP = dsPIC_Object->TMR4IP;
}
// </editor-fold>

void Initialize() {
    Setup_dsPIC();
    dsPicConfigValues dsPicConfig;
    SetConfigValues(&dsPicConfig);

    SetupPPS(&dsPicConfig);
    SetupUART(&dsPicConfig);
    SetupMI2C(&dsPicConfig);
    SetupOC(&dsPicConfig);
    SetupQEI(&dsPicConfig);
    SetupTMR(&dsPicConfig);
}

// <editor-fold defaultstate="collapsed" desc="UART">

void SendUART1(uint8_t byte) {
    _U1TXIF = 0;
    U1TXREG = byte;
}

uint8_t RecieveUART1() {
    _U1RXIF = 0;
    uint8_t temp;
    temp = U1RXREG;
    return temp;
}

void SendUART2(uint8_t datas) {
    _U2TXIF = 0;
    U2TXREG = datas;
}

uint8_t RecieveUART2() {
    _U2RXIF = 0;
    uint8_t temp;
    temp = U2RXREG;
    return temp;
}

void __attribute__((interrupt, auto_psv)) _U1ErrInterrupt(void) {
    _U1EIF = 0;
    if (U1STAbits.FERR == 1) {
        return;
    }

    if (U1STAbits.OERR == 1) {
        U1STAbits.OERR = 0;
        return;
    }
}

void __attribute__((interrupt, auto_psv)) _U2ErrInterrupt(void) {
    _U2EIF = 0;
    if (U2STAbits.FERR == 1) {
        return;
    }

    if (U2STAbits.OERR == 1) {
        U2STAbits.OERR = 0;
        return;
    }
}
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="I2C_Master">

void StartMI2C() {
    _MI2C1IF = 0;
    I2C1CONbits.SEN = 1;
}

void SendMI2C(uint8_t datas) {
    _MI2C1IF = 0;
    I2C1TRN = datas;
}

uint8_t ReadMI2C() {
    uint8_t temp;
    _MI2C1IF = 0;
    while (!_MI2C1IF);
    temp = I2C1RCV;
    return temp;
}

void StopMI2C() {
    _MI2C1IF = 0;
    I2C1CONbits.PEN = 1;
}

void RxOnMI2C() {
    I2C1CONbits.RCEN = 1;
}

void RestartMI2C() {
    _MI2C1IF = 0;
    I2C1CONbits.RSEN = 1;
}

void SendAckMI2C() {
    _MI2C1IF = 0;
    I2C1CONbits.ACKDT = 0;
    I2C1CONbits.ACKEN = 1;
}

void SendNackMI2C() {
    _MI2C1IF = 0;
    I2C1CONbits.ACKDT = 1;
    I2C1CONbits.ACKEN = 1;
}
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="OutPutCompare">

static void SetDuty(OutputCompare ocNum, unsigned int duty, ActiveDirection pinAction) {
    volatile unsigned int* ocrsArray[4] = {&OC1RS, &OC2RS, &OC3RS, &OC4RS};
    volatile unsigned int* period = NULL;

    if ((ocNum == OutputCompare1) || (ocNum == OutputCompare2)) {
        period = &PR2;
    } else {
        period = &PR3;
    }
    if (duty > *period) {
        duty = *period;
    }

    if (pinAction == ActiveHigh) {
        *ocrsArray[ocNum] = duty;
    } else {
        *ocrsArray[ocNum] = *period - duty;
    }
}

void SetDutyMicroSec(OutputCompare ocNum, float microSec, ActiveDirection pinAction) {

    volatile unsigned int* OCRS_add[4] = {&OC1RS, &OC2RS, &OC3RS, &OC4RS};
    volatile unsigned int* period;
    float TCKPS;

    if (_changeBeforeOC[ocNum].microSec != microSec) {
        if ((ocNum == OutputCompare1) || (ocNum == OutputCompare2)) {
            TCKPS = T2CKPS;
            period = &PR2;
        } else {
            TCKPS = T3CKPS;
            period = &PR3;
        }

        _changeBeforeOC[ocNum].real_data = fabs(((microSec / 1000000.0) * FCY) / (TCKPS));
        if (_changeBeforeOC[ocNum].real_data >= *period) {
            _changeBeforeOC[ocNum].real_data = *period;
        }
        _changeBeforeOC[ocNum].microSec = microSec;
    }
    if (pinAction == ActiveHigh) {
        *OCRS_add[ocNum] = _changeBeforeOC[ocNum].real_data;
    } else {
        *OCRS_add[ocNum] = *period - _changeBeforeOC[ocNum].real_data;
    }
}

void SetDutyPercent(OutputCompare ocNum, float percent, ActiveDirection pinAction) {
    float duty = 0;

    if (fabs(percent) > 100.0) {
        percent = 100.0;
    }

    if ((ocNum == OutputCompare1) || (ocNum == OutputCompare2)) {
        duty = PR2 * (percent / 100.0);
    } else {
        duty = PR3 * (percent / 100.0);
    }
    SetDuty(ocNum, duty, pinAction);
}
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Timer">

static void SetTimerInterrupt(Timer timerNum, InterruptEnableEnum interruptEnable) {
    switch (timerNum) {
        case Timer1:
            _T1IF = 0;
            _T1IE = (interruptEnable == InterruptEnable);
            break;
        case Timer2:
            _T2IF = 0;
            _T2IE = (interruptEnable == InterruptEnable);
            break;
        case Timer3:
            _T3IF = 0;
            _T3IE = (interruptEnable == InterruptEnable);
            break;
        case Timer4:
            _T4IF = 0;
            _T4IE = (interruptEnable == InterruptEnable);
            break;
        case Timer5:
            _T5IF = 0;
            _T5IE = (interruptEnable == InterruptEnable);
            break;
    }
}

static void SetTimerConfig(Timer timerNum, uint8_t tckps) {
    switch (timerNum) {
        case Timer1:
            T1CONbits.TCKPS = tckps;
            T1CONbits.TON = true;
            break;
        case Timer2:
            T2CONbits.TCKPS = tckps;
            T2CONbits.TON = true;
            break;
        case Timer3:
            T3CONbits.TCKPS = tckps;
            T3CONbits.TON = true;
            break;
        case Timer4:
            T4CONbits.TCKPS = tckps;
            T4CONbits.TON = true;
            break;
        case Timer5:
            T5CONbits.TCKPS = tckps;
            T5CONbits.TON = true;
            break;
    }
}

void SetDelay(Timer timerNum, TimerMode mode, float sec, InterruptEnableEnum interruptEnable) {
    float TMR = 0;
    const float PRx_MAX_VAL = 65535.0;
    float TCKPS = 1.0;
    uint8_t i = 0;
    volatile unsigned int* TMR_add[5] = {&TMR1, &TMR2, &TMR3, &TMR4, &TMR5};
    volatile unsigned int* PR_add[5] = {&PR1, &PR2, &PR3, &PR4, &PR5};

    if ((_changeBeforeTMR[timerNum].Mode != mode)
            || (_changeBeforeTMR[timerNum].Sec != sec)) {
        for (i = 0; i < 4; i++) {
            TCKPS = pow(8.0, i);
            if (TCKPS > 64.0) {
                TCKPS = 256.0;
            }
            TMR = (((sec / (pow(1000.0, mode + 1))) * FCY) / (TCKPS));
            if (TMR <= PRx_MAX_VAL) {
                _changeBeforeTMR[timerNum].real_data = TMR;
                break;
            } else if (i == 3) {
                _changeBeforeTMR[timerNum].real_data = 0xFFFF;
            }
        }
        _changeBeforeTMR[timerNum].TkcpsValue = i;
        _changeBeforeTMR[timerNum].Mode = mode;
        _changeBeforeTMR[timerNum].Sec = sec;
    }

    *TMR_add[timerNum] = 0;
    *PR_add[timerNum] = _changeBeforeTMR[timerNum].real_data;
    SetTimerInterrupt(timerNum, interruptEnable);
    SetTimerConfig(timerNum, _changeBeforeTMR[timerNum].TkcpsValue);
}
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="QEI">

int16_t ReadQEI1() {
    int16_t temp = 0;
    temp = (int16_t) POS1CNT;
    POS1CNT = 0;
    return temp;
}

int16_t ReadQEI2() {
    int16_t temp = 0;
    temp = (int16_t) POS2CNT;
    POS2CNT = 0;
    return temp;
}
// </editor-fold>

