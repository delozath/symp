/*
 * adc_single_timer.c
 *
 *  Created on: 09/07/2018
 *      Author: delozath
 */

#include <msp430g2553.h>


// Global variables
volatile short    int state = 0;
volatile unsigned int adc   = 0;

// Declare
void timer_setup(void);
void adc_setup(void);

void main(void)
{
    {
        WDTCTL  = WDTPW + WDTHOLD;
        DCOCTL  = CALDCO_1MHZ;
        BCSCTL1 = CALBC1_1MHZ;
        P1SEL  |= BIT2;

        timer_setup();
        adc_setup();


        while(1)
        {
            _BIS_SR(CPUOFF + GIE);        // LPM0
        }

    }
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
    if (state == 1)
    {
      state      = 0;
      ADC10CTL0 ^= ENC + ADC10SC;
      adc        = ADC10MEM;               // Read
    }
    __bic_SR_register_on_exit(CPUOFF);        // Return to active mode }
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    if (state == 0)
    {
      ADC10CTL0 |= ENC + ADC10SC;       // Sampling and conversion start
      state      = 1;
    }
   __bic_SR_register_on_exit(CPUOFF);
}

// Define
void adc_setup(void)
{

    ADC10CTL1 = INCH_2 + ADC10DIV_2 ;
    ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON + ADC10IE;
    ADC10AE0 |= BIT2;
}

void timer_setup(void)
{
    TA0CTL = TASSEL_2 + MC_1 + ID_3;
    CCR0   = 0XFF00;
    CCTL0  = CCIE;
}
