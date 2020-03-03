# CSCC69-A2

## Tables
{Fred Send Data / Insert Here}

## Algorithms Comparison
Using OPT as the yardstick, we can see that 
FIFO suffered from "Belady's Anomaly" as the Miss Count increased when the algorithm was given more memory.
Clock (with one ref-bit) had a low overhead when given more memory.
Exact LRU on average preformed very well (close to OPT) but it is costly to implement.

| Overall | Performance |
|---|---|
| OPT  | Fastest |
| Exact LRU | Fast |
| Clock (with one ref-bit) | Medium |
| FIFO | Slow |

## LRU Data Analysis With Increasing Memory

