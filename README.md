Lab 5
====

## Pre-Lab

**How long will it take the timer to roll over?**

It should take 16ms before the timer rolls over since it counts from `0x0000` to `0xFFFF` and each count lasts (1/8MHz).

**How long does each timer count last?**

With the clock at 8MHz, each timer count should last 125ps. However, use of the logic analyzer lends me to believe the clock is actually operating at 1MHz with a period of 1us.

