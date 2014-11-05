Lab 5
====

## Pre-Lab

**How long will it take the timer to roll over?**

It should take 16ms before the timer rolls over since it counts from `0x0000` to `0xFFFF` and each count lasts (1/8MHz).

**How long does each timer count last?**

With the clock at 8MHz, each timer count should last 125ps. However, use of the logic analyzer lends me to believe the clock is actually operating at 1MHz with a period of 1us since a count of roughly 500 would translate to roughly 500us on the logic analyzer.

![alt text](http://i.imgur.com/rKiKi6n.png "GO ARMY, BEAT AIR FORCE")


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
