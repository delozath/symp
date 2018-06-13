#include <msp430g2553.h>

void timer_output(){
      TACTL  = TACLR;
      TACTL  = TASSEL_2 + ID_3 + MC_2;
}

volatile short int state = 0;
int main(void)
{
  //Config
  WDTCTL = WDTPW + WDTHOLD;            // Stop WDT
  P1DIR |= BIT0;                       // P1.0 output
  TACTL  = TASSEL_2 + ID_3 + MC_2;     // SMCLK


 while(1)

  {
    switch(state)
    {
      case 0:
          if ( (TACTL & TAIFG)==TAIFG ){
              timer_output();
              state  = 1;
          }
          break;
      case 1:
          P1OUT ^= BIT0;
          state  = 0;
          break;

    }
  }

}
