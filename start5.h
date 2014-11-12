#ifndef START5_H_
#define START5_H_

//-----------------------------------------------------------------
// Name:  Jaksha, Clayton, B.
// File:	start5.h
// Date:	Fall 2014
// Purp:	Include file for the MSP430
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Page 76 : MSP430 Optimizing C/C++ Compiler v 4.3 User's Guide
//-----------------------------------------------------------------
typedef		unsigned char		int8;
typedef		unsigned short		int16;
typedef		unsigned long		int32;
typedef		unsigned long long	int64;

#define		TRUE				1
#define		FALSE				0

//-----------------------------------------------------------------
// Function prototypes found in lab5.c
//-----------------------------------------------------------------
void initMSP430();
__interrupt void pinChange (void);
__interrupt void timerOverflow (void);


//-----------------------------------------------------------------
// Each PxIES bit selects the interrupt edge for the corresponding I/O pin.
//	Bit = 0: The PxIFGx flag is set with a low-to-high transition
//	Bit = 1: The PxIFGx flag is set with a high-to-low transition
//-----------------------------------------------------------------

#define		IR_PIN			(P2IN & BIT6)
#define		HIGH_2_LOW		P2IES |= BIT6
#define		LOW_2_HIGH		P2IES &= ~BIT6

#define		BUTTON_TWO			0x9E6148B6
#define		BUTTON_FOUR			0x9E6128D6
#define		BUTTON_FIVE			0x9E61A856
#define		BUTTON_SIX			0x9E616896
#define		BUTTON_EIGHT		0x9E6118E6
#define		averageLogic0Pulse	520
#define		averageLogic1Pulse	1623
#define		averageStartPulse	4405
#define		minLogic0Pulse		averageLogic0Pulse - 125
#define		maxLogic0Pulse		averageLogic0Pulse + 125
#define		minLogic1Pulse		averageLogic1Pulse - 125
#define		maxLogic1Pulse		averageLogic1Pulse + 125
#define		minStartPulse		averageStartPulse - 125
#define		maxStartPulse		averageStartPulse + 125



#endif /* START5_H_ */
