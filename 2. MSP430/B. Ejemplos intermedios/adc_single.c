/*
 * adc_single.c
 *
 *  Created on: 09/07/2018
 *      Author: delozath
 */
#include <msp430g2553.h>


// Global variables
unsigned int adc=0;

// Declare
void adc_setup(void);

void main(void)
{
    {
        WDTCTL  = WDTPW + WDTHOLD;
        DCOCTL  = CALDCO_1MHZ;
        BCSCTL1 = CALBC1_1MHZ;
        P1SEL  |= BIT2;

        adc_setup();

        while(1)
        {
            __delay_cycles(1000);         // Wait
            ADC10CTL0 |= ENC + ADC10SC;   // Sampling and conversion start
            _BIS_SR(CPUOFF + GIE);        // LPM0
        }

    }
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
    adc = ADC10MEM;               // Read
    __bic_SR_register_on_exit(CPUOFF);        // Return to active mode }
}

// Define
void adc_setup(void)
{

    ADC10CTL1 = INCH_2 + ADC10DIV_2 ;
    ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON + ADC10IE;
    ADC10AE0 |= BIT2;
}
















