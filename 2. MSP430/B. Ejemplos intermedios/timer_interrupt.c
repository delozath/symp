#include <msp430g2553.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;

  /* 1. Clock config */
  DCOCTL  = CALDCO_1MHZ;
  BCSCTL1 = CALBC1_1MHZ;

  /* 2. Timer0 config */
  TA0CTL = TASSEL_2 + MC_1 + ID_3;
  CCR0   = 0XFF00;

  /* 2. Ports config */
  P1DIR &= 0x00;
  P1DIR |= BIT0 + BIT6;
  P1REN |= BIT3;
  P1OUT |= BIT3;                  //Select pull-up mode for P1.3

  /*2.1. Port interrupt config */
  P1IES |=  BIT3;                  // P1.3 Hi/lo edge
  P1IFG &= ~BIT3;                  // P1.3 IFG cleared

  /* 3. Interrupts enabled */
  CCTL0  = CCIE;                   // CCR0 interrupt enabled
  P1IE  |= BIT3;                   // P1.3 interrupt enabled
  while(1)
  {
      _BIS_SR(CPUOFF + GIE);       // LPM0 interrupt
  }
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
   P1OUT ^= BIT0;
   __bic_SR_register_on_exit(CPUOFF);
}


// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
   P1OUT ^= BIT6;
   P1IFG &= ~BIT3;                     // P1.3 IFG cleared
   __bic_SR_register_on_exit(CPUOFF);
}
