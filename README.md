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
