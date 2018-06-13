#include <msp430.h>

/*
 * main.c
 */
  int main(void) {
    /*Configuracion del MSP430*/
    /*======*/
    WDTCTL = WDTPW | WDTHOLD;   // Disable watchdog timer
    P1DIR |= BIT0;
    P1OUT  = 0x01;

    /*Estado S*/
    /*======*/
    volatile static const unsigned int L0 = 0x1000;
    volatile static const unsigned int L1 = 0xFFFA;
    volatile unsigned int L;
    volatile unsigned int i;
    volatile unsigned int S;

    S = 0;
    L = L0;


    while(1){
        switch (S) {
          case 0:
              for (i=0;i<L;i++){
                          asm( " nop");
                   }
              if (P1OUT == 0){
                  S = 1;
              }else
              {
                  S = 2;
              }
              break;

          case 1:
              S     = 0;
              L     = L1;
              P1OUT = 1;
              break;

          case 2:
              S     = 0;
              L     = L0;
              P1OUT = 0;
              break;
        }
    }
    return 0;
}
