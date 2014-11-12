//-----------------------------------------------------------------
// Name:	Jaksha
// File:	main.c
// Date:	Fall 2014
// Purp:	Demo the decoding of an IR packet
//-----------------------------------------------------------------
#include <msp430g2553.h>
#include "start5.h"

extern void init();
extern void initNokia();
extern void clearDisplay();
extern void drawBlock(unsigned char row, unsigned char col);
extern void drawBlankBlock(unsigned char row, unsigned char col);

int32	packetData[48];
int8	packetIndex = 0;
unsigned char packet_flag=FALSE;

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void main(void) {

	initMSP430();				// Setup MSP to process IR and buttons
	init();
	initNokia();

	unsigned char	x, y, button_press;
	unsigned char color=1;
	int32 bitstring=0x00000000;
	int32	i;
	int8	packetIndex2=0;
	button_press = FALSE;

	clearDisplay();				//get the display all fired up and enable interrupts
	x=4; y=4;
	drawBlock(y,x);
	_enable_interrupt();

	while(1)  {
		if (packet_flag) {
			_disable_interrupt();
			packetIndex2=0;
			while ((packetData[packetIndex2]!=2)&&(packetIndex2<50))	//this looks for the start bit
			{
				packetIndex2++;
			}
			packetIndex2++;
			while (packetIndex2<33)					//after finding the start bit, we begin shuffling the array into one register
			{
				bitstring+=packetData[packetIndex2];
				bitstring<<=1;
				packetIndex2++;
			}
			if (bitstring==BUTTON_FIVE)
			{
				color ^= 1;
				P1OUT |= BIT0;                     // toggle LEDs
			} else if (bitstring==BUTTON_TWO)
			{
				if (y>=1) y=y-1;
				button_press = TRUE;
				P1OUT &= ~BIT0;
			} else if (bitstring==BUTTON_FOUR)
			{
				if (x>=1) x=x-1;
				button_press = TRUE;
				P1OUT ^= BIT0;
			} else if (bitstring==BUTTON_SIX)
			{
				if (x<=10) x=x+1;
				button_press = TRUE;
				P1OUT ^= BIT6;
			} else if (bitstring==BUTTON_EIGHT)
			{
				if (y<=6) y=y+1;
				button_press = TRUE;
				P1OUT &= ~(BIT0|BIT6);
			}
			init();
			initNokia();						//for some reason `initNokia()` is causing some weird writing issues. Fix undetermined as of yet.
			if (button_press) {					//this is the part of the code that actually writes the bit onto the screen
				button_press = FALSE;
				if (color==1)
				{
					drawBlock(y,x);
				} else
				{
					drawBlankBlock(y,x);
				}
			}
			for (i=0;i<0xFFFFF;i++);				//a little delay in case of ghost bits
			initMSP430();
			bitstring=0x00000000;
			packetIndex=0;
			_enable_interrupt();
			packet_flag=0;
		} else
		{
			bitstring=0x00000000;
		}
	} // end infinite loop
} // end main

// -----------------------------------------------------------------------
// In order to decode IR packets, the MSP430 needs to be configured to
// tell time and generate interrupts on positive going edges.  The
// edge sensitivity is used to detect the first incoming IR packet.
// The P2.6 pin change ISR will then toggle the edge sensitivity of
// the interrupt in order to measure the times of the high and low
// pulses arriving from the IR decoder.
//
// The timer must be enabled so that we can tell how long the pulses
// last.  In some degenerate cases, we will need to generate a interrupt
// when the timer rolls over.  This will indicate the end of a packet
// and will be used to alert main that we have a new packet.
// -----------------------------------------------------------------------
void initMSP430() {

	IFG1=0; 					// clear interrupt flag1
	WDTCTL=WDTPW+WDTHOLD; 		// stop WD

	BCSCTL1 = CALBC1_8MHZ;
	DCOCTL = CALDCO_8MHZ;

	P1DIR |= BIT0|BIT6;                     // set LEDs to output

	P2SEL  &= ~BIT6;						// Setup P2.6 as GPIO not XIN
	P2SEL2 &= ~BIT6;
	P2DIR &= ~BIT6;
	P2IFG &= ~BIT6;						// Clear any interrupt flag
	P2IE  |= BIT6;						// Enable PORT 2 interrupt on pin change

	HIGH_2_LOW;
	P1DIR |= BIT0 | BIT6;				// Enable updates to the LED
	P1OUT &= ~(BIT0 | BIT6);			// An turn the LED off

	TA0CCR0 = 0x8000;					// create a 16mS roll-over period
	TACTL &= ~TAIFG;					// clear flag before enabling interrupts = good practice
	TACTL = ID_3 | TASSEL_2 | MC_1;		// Use 1:1 presclar off MCLK and enable interrupts

	_enable_interrupt();
}

// -----------------------------------------------------------------------
// Since the IR decoder is connected to P2.6, we want an interrupt
// to occur every time that the pin changes - this will occur on
// a positive edge and a negative edge.
//
// Negative Edge:
// The negative edge is associated with end of the logic 1 half-bit and
// the start of the logic 0 half of the bit.  The timer contains the
// duration of the logic 1 pulse, so we'll pull that out, process it
// and store the bit in the global irPacket variable. Going forward there
// is really nothing interesting that happens in this period, because all
// the logic 0 half-bits have the same period.  So we will turn off
// the timer interrupts and wait for the next (positive) edge on P2.6
//
// Positive Edge:
// The positive edge is associated with the end of the logic 0 half-bit
// and the start of the logic 1 half-bit.  There is nothing to do in
// terms of the logic 0 half bit because it does not encode any useful
// information.  On the other hand, we going into the logic 1 half of the bit
// and the portion which determines the bit value, the start of the
// packet, or if the timer rolls over, the end of the ir packet.
// Since the duration of this half-bit determines the outcome
// we will turn on the timer and its associated interrupt.
// -----------------------------------------------------------------------
#pragma vector = PORT2_VECTOR			// This is from the MSP430G2553.h file

__interrupt void pinChange (void) {

	int8	pin;
	int16	pulseDuration;

	P2IFG &= ~BIT6;
	if (IR_PIN)		pin=1;	else pin=0;

	switch (pin) {					// read the current pin level
		case 0:						// !!!!!!!!!NEGATIVE EDGE!!!!!!!!!!
			pulseDuration = TAR;
			if ((pulseDuration>minStartPulse)&&(pulseDuration<maxStartPulse))
			{
				pulseDuration=2;
			} else if ((pulseDuration>minLogic0Pulse)&&(pulseDuration<maxLogic0Pulse))
			{
				pulseDuration=0;
			} else if ((pulseDuration>minLogic1Pulse)&&(pulseDuration<maxLogic1Pulse))
			{
				pulseDuration=1;
			}
			packetData[packetIndex++] = pulseDuration;
			LOW_2_HIGH; 				// Setup pin interrupr on positive edge
			break;

		case 1:							// !!!!!!!!POSITIVE EDGE!!!!!!!!!!!
			TAR = 0x0000;						// time measurements are based at time 0
			HIGH_2_LOW; 						// Setup pin interrupr on positive edge
			break;
	} // end switch
	if (packetIndex>33)
	{
		packet_flag=1;
	}
} // end pinChange ISR



#pragma vector = TIMER0_A1_VECTOR			// This is from the MSP430G2553.h file
__interrupt void timerOverflow (void) {

	TACTL &= ~TAIFG;
}


