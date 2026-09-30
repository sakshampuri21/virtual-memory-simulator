\# Virtual Memory \& Page Replacement Simulator



A modular C++ simulator that tracks page faults and hits for 1-8 configurable memory frames.



\## Features

\- FIFO, LRU and Optimal page replacement (Optimal is the theoretical baseline)

\- Compares the policies on random, sequential and locality-heavy reference patterns by fault rate and hit ratio

\- Demonstrates Belady's anomaly under FIFO, where adding frames increases page faults

\- Applies a sliding-window working-set model to measure temporal locality



\## Project structure

```

include/

&#x20; replacement\_policy.hpp   base interface for all policies

&#x20; fifo.hpp, lru.hpp, optimal.hpp

&#x20; policy\_factory.hpp       creates a policy by type

&#x20; simulator.hpp            runs a policy, counts hits and faults

&#x20; generators.hpp           reference pattern generators

&#x20; working\_set.hpp          working-set analysis

&#x20; types.hpp

src/

&#x20; one .cpp file per header, plus main.cpp

```



\## Build and run

```

g++ -std=c++17 -O2 -Iinclude src/\*.cpp -o vmsim

./vmsim              # run everything

./vmsim compare      # policy comparison for 1-8 frames

./vmsim belady       # Belady's anomaly demo

./vmsim workingset   # working-set analysis

```

On Windows, use `vmsim.exe` instead of `./vmsim`.



\## Sample output: Belady's anomaly (FIFO)

Reference string: 1 2 3 4 1 2 5 1 2 3 4 5



| Frames | Faults |

|--------|--------|

| 3      | 9      |

| 4      | 10     |



With 4 frames FIFO faults more than with 3, which is Belady's anomaly.



\## Notes

\- Optimal needs the whole reference string in advance, so it can't be used in a real OS. It is used here only as a lower bound on faults.

\- A smaller working set means stronger locality, so fewer frames are needed.

