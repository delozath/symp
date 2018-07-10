#include <msp430g2553.h>

volatile short int state = 0;

void timer_reset( ){
      TACTL    = TACLR;
      if (state==0){
          TACTL    = TASSEL_2 + ID_3 + MC_1;
          TACCR0   = 0xeeee;
      }
      else{
          TACTL    = TASSEL_2 + ID_3 + MC_1;
          TACCR0   = 0xffee;
      }

      TACCTL0 ^= CCIFG;
}


int main(void)
{
  //Config
  WDTCTL  = WDTPW + WDTHOLD;            // Stop WDT
  DCOCTL  = CALDCO_1MHZ;
  BCSCTL1 = CALBC1_1MHZ;
  P1DIR  |= BIT0;                       // P1.0 output
  TACTL   = TASSEL_2 + ID_3 + MC_1;     // SMCLK
  TACCR0  = 10;


 while(1)

  {
    switch(state)
    {
      case 0:
          if ( (TA0CCTL0 & CCIFG)==CCIFG ){
              timer_reset();
              state    = 1;
              P1OUT   ^= BIT0;
          }
          break;
      case 1:
          if ( (TA0CCTL0 & CCIFG)==CCIFG ){
              timer_reset();
              state    = 0;
              P1OUT   ^= BIT0;
          }
          break;
    }
  }

}
