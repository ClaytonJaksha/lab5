Lab 5
====

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

| Command  |           Data String           |
|----------|:-------------------------------:|
| 0        | 0011110011000010000100011110111 |
| 1        | 0011110011000011000100001110111 |
| 2        | 0011110011000010100100010110111 |
| 3        | 0011110011000011100100000110111 |
| Power      | 0011110011000011000000001111111 |
| ~~Vol +~~ Play     | 0011110011000010100000010111111 |
| ~~Volt -~~ Stop     | 0011110011000010110101010010101 |
| ~~Ch +~~ search>> | 0011110011000010110000010011111 |
| ~~Ch -~~ <<search | 0011110011000011010000001011111 |
| * *note my remote control (DFEC #6) does not have the buttons with strikethrough* |
