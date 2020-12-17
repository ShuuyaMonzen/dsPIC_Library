#include <stdio.h>
#include <stdlib.h>
#include "BasicLibrary/BasicLibrary_dsPIC33FJ128MC802.h"

int main(void) {

    // ポインタ型の変数を生成
    dsPIC* dsPICObj = dsPICInitialize();
    
    while(1){
        dsPICObj->SendUART1(0xAA);
        __delay_ms(100);
    }
    return EXIT_SUCCESS;
}

