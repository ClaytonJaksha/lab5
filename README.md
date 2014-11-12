Lab 5
====
#### Clayton Jaksha | ECE 382 | Dr. York | M2A

## Objective and Purpose
### Objective

The objective of this lab is to use timers and interrupts to reverse engineer a remote control.

### Purpose

To practically use timers and interrupts in an actual system and gain a better understanding of IR transmitters.

## Pre-Lab

**How long will it take the timer to roll over?**

It should take 16ms before the timer rolls over since it counts from `0x0000` to `0xFFFF` and each count lasts (1/8MHz).

**How long does each timer count last?**

With the clock at 8MHz, each timer count should last 125ps. However, use of the logic analyzer lends me to believe the clock is actually operating at 1MHz with a period of 1us since a count of roughly 500 would translate to roughly 500us on the logic analyzer.

![alt text](http://i.imgur.com/rKiKi6n.png "GO ARMY, BEAT AIR FORCE")

|  Type          | avg time (s) | stdv time (s) | avg cnts | stdv cnts |
|----------------|:------------:|---------------|----------|-----------|
| start logic 0  | 0.008895333  | 2.39687E-05   | 8895.333 | 23.96873  |
| start logic 1  | 0.004405889  | 2.01646E-05   | 4405.889 | 20.1646   |
| data 0 logic 0 | 0.0005958    | 3.3852E-05    | 595.8    | 33.85203  |
| data 0 logic 1 | 0.000520568  | 2.66679E-05   | 520.5682 | 26.66793  |
| data 1 logic 0 | 0.000598269  | 3.02215E-05   | 598.2687 | 30.22153  |
| data 1 logic 1 | 0.001623563  | 2.20494E-05   | 1623.563 | 22.04944  |
| stop logic 0   | 0.000506778  | 0.000190962   | 506.7778 | 190.9619  |
| stop logic 1   | 0.039301     | 2.24611E-05   | 39301    | 22.46108  |

***Using 5 standard deviations, I calcuated a range for each duration***


|  Type          | Duration Max (ms) | Duration Min (ms) | Timer A Counts (Max) | Timer A Counts (Min) |
|----------------|:-----------------:|-------------------|----------------------|----------------|
| start logic 0  | 9.015176981       | 8.775489685       | 9015.177             | 8775.49        |
| start logic 1  | 4.506711891       | 4.305065887       | 4506.712             | 4305.066       |
| data 0 logic 0 | 0.76506013        | 0.42653987        | 765.0601             | 426.5399       |
| data 0 logic 1 | 0.653907835       | 0.387228529       | 653.9078             | 387.2285       |
| data 1 logic 0 | 0.749376302       | 0.447161012       | 749.3763             | 447.161        |
| data 1 logic 1 | 1.733809709       | 1.513315291       | 1733.81              | 1513.315       |
| stop logic 0   | 1.461587241       | -0.44803169       | 1461.587             | -448.032       |
| stop logic 1   | 39.41330539       | 39.18869461       | 39413.31             | 39188.69       |

| Command  |           Data String           |
|----------|:-------------------------------:|
| 0        | 0x1E6108F7 |
| 1        | 0x1E618877 |
| 2        | 0x1E6148B7 |
| 3        | 0x1E61C837 |
| Power      | 0x1E61807F |
| ~~Vol +~~ Play     | 0x1E6140BF |
| ~~Volt -~~ Stop     | 0x1E616A95 |
| ~~Ch +~~ search>> | 0x1E61609F |
| ~~Ch -~~ <<search | 0x1E61A05F |
| * *note my remote control (DFEC #6) does not have the buttons with strikethrough* |

## Preliminary Design

#### Basic Functionality

The idea behind basic functionality is to have an LED toggle with a remote control that utilizes an interrupt service routine. In order to make this work, I will need to interrupt on each IR edge from the remote control, time the length of the `1` from the remote control to determine if it is sending a `0` or `1`, then interrupt when I have received an adequate number of `0`s and `1`s.

After interrupting, I will compile my array of `0`s and `1`s into a single register, compare that register with my predefined values for button presses (explored in pre-lab/day 1 activities), then perform an action based on the button that was pressed.

During this process, it would be smart to disable maskable interrutps since any 'ghost' signals from my remote (or others) could interrupt my sequence and throw everything off. If, for some reason, I get a signal that does not match any predefined button, I will merely let the signal pass, reset all my indices, and try again.

#### Remote-Control Etch-A-Sketch

With etch-a-sketch functionality, I simply aim to operate my etch-a-sketch made in lab 4 with a remote control. The process will be a schmorgeshboard of basic functionality for this lab and my etch-a-sketch code from lab 4. Basically, I will reintroduce the variables I used from the lab 4 code and then implement the `if` statements from lab 4 within my basic functionality code.

I will also need to include the `nokia.asm` code from lab 4 and any display initalization.

## Code Walkthrough
```
#include <msp430g2553.h>
#include "start5.h"
int32 packetData[48];
int8 packetIndex = 0;
unsigned char packet_flag=FALSE;
```
```
void main(void) {
initMSP430(); // Setup MSP to process IR and buttons
int32 bitstring=0x00000000;
int32 i;
int8 packetIndex2=0;
while(1) {
if (get_some) {
_disable_interrupt();
packetIndex2=0;
while (packetData[packetIndex2]!=2)
{
packetIndex2++;
}
packetIndex2++;
while (packetIndex2<33)
{
bitstring+=packetData[packetIndex2];
bitstring<<=1;
packetIndex2++;
}
if (bitstring==BUTTON_FIVE)
{
P1OUT |= BIT0; // toggle LEDs
} else if (bitstring==BUTTON_TWO)
{
P1OUT &= ~BIT0;
} else if (bitstring==BUTTON_FOUR)
{
P1OUT ^= BIT0;
} else if (bitstring==BUTTON_SIX)
{
P1OUT ^= BIT6;
} else if (bitstring==BUTTON_EIGHT)
{
P1OUT &= ~(BIT0|BIT6);
}
for (i=0;i<0xFFFFF;i++);
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
```
```
void initMSP430() {
IFG1=0; // clear interrupt flag1
WDTCTL=WDTPW+WDTHOLD; // stop WD
BCSCTL1 = CALBC1_8MHZ;
DCOCTL = CALDCO_8MHZ;
P1DIR |= BIT0|BIT6; // set LEDs to output
P2SEL &= ~BIT6; // Setup P2.6 as GPIO not XIN
P2SEL2 &= ~BIT6;
P2DIR &= ~BIT6;
P2IFG &= ~BIT6; // Clear any interrupt flag
P2IE |= BIT6; // Enable PORT 2 interrupt on pin change
HIGH_2_LOW;
P1DIR |= BIT0 | BIT6; // Enable updates to the LED
P1OUT &= ~(BIT0 | BIT6); // An turn the LED off
TA0CCR0 = 0x8000; // create a 16mS roll-over period
TACTL &= ~TAIFG; // clear flag before enabling interrupts = good practice
TACTL = ID_3 | TASSEL_2 | MC_1; // Use 1:1 presclar off MCLK and enable interrupts
_enable_interrupt();
}
```
```
#pragma vector = PORT2_VECTOR // This is from the MSP430G2553.h file
__interrupt void pinChange (void) {
int8 pin;
int16 pulseDuration;
P2IFG &= ~BIT6;
if (IR_PIN) pin=1; else pin=0;
switch (pin) { // read the current pin level
case 0: // !!!!!!!!!NEGATIVE EDGE!!!!!!!!!!
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
LOW_2_HIGH; // Setup pin interrupr on positive edge
break;
case 1: // !!!!!!!!POSITIVE EDGE!!!!!!!!!!!
TAR = 0x0000; // time measurements are based at time 0
HIGH_2_LOW; // Setup pin interrupr on positive edge
break;
} // end switch
if (packetIndex>33)
{
packet_flag=1;
}
} // end pinChange ISR
#pragma vector = TIMER0_A1_VECTOR // This is from the MSP430G2553.h file
__interrupt void timerOverflow (void) {
TACTL &= ~TAIFG;
}

```

## Debugging

Debugging was primarily done by looking at the Nokia 1202 display and the stored register and expression values within CCS-6.0's debugging feature.

## Testing Methodology/Results

#### Testing Methodology

#### Results
The code works!
##### Basic Functionality

##### A Functionality


## Observations and Conclusion
#### Observations

* Reusing previous .c and .h files can make coding faster and modular.
* Writing fine values onto a screen is difficult.
* Structures and fun and easy to use. They enable a group of information to be stored in an organized manner.

#### Conclusion

The etch-a-sketch and pong funcitons worked according to specs. Army is fully prepared to beat Air Force next week.

## Documentation

None


# [ON BRAVE OL' ARMY TEAM!](http://www.youtube.com/watch?v=-HNz02SNTLY)
![alt text](http://usarmy.vo.llnwd.net/e2/c/images/2011/11/07/226002/size0.jpg "GO ARMY, BEAT AIR FORCE")
