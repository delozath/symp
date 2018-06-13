#include <msp430g2553.h>

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    P1DIR  = BIT0 + BIT6;
    P1REN  = BIT3;
    P1IN   = ~BIT3 | P1IN;
    P1OUT  = BIT3 + BIT0;

    volatile short int states = 0;
    while(1)
    {
        switch (states)

        {
            case 0:
                if((P1IN & BIT3)!=BIT3)
                {
                    states = 1;
                }
                break;

            case 1:
                __delay_cycles(0X080000);
                P1OUT ^= BIT6 + BIT0;
                states = 0;
                break;
        }
   }
}
