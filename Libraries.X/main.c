#include <stdlib.h>
#include "lib/BasicLibrary/BasicLibrary_dsPIC33FJ128MC802.h"

dsPIC* dsPICObj;

int main(void) {

    //初期設定実行
    dsPICObj = dsPICInitialize();
    
    while(1){
        dsPICObj->sendUART1(0xAA);
        __delay_ms(100);
    }
    
    return 0;
}

