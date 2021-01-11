#include <stdlib.h>
#include "lib/BasicLibrary/BasicLibrary_dsPIC33FJ128MC802.h"

dsPIC* dsPICObj;

int main(void) {

    //初期設定実行
    dsPICObj = dsPICInitialize();
    TRISA = 0;
    LATA = 0;
    if(dsPICObj->dsPicConfig->UART1BaudRate == _9600bps){
        LATA = 0x1;
    }
    
    while(1){
        dsPICObj->sendUART1(0xAA);
        __delay_ms(1000);
    }
    
    return 0;
}

