Virtual Memory and Page Replacement Simulator



About



This is a modular C++ simulator that tracks page faults and hits for 1 to 8 configurable memory frames. It compares three page replacement policies (FIFO, LRU and Optimal) on different memory access patterns.



What it does



\- Implements FIFO, LRU and Optimal page replacement. Optimal is used as the theoretical best case.

\- Compares the policies on random, sequential and locality-heavy access patterns by fault rate and hit ratio.

\- Demonstrates Belady's anomaly under FIFO, where adding more frames increases page faults.

\- Applies a sliding-window working-set model to measure how much the page references show temporal locality.



How the policies work



FIFO removes the page that has been in memory the longest.



LRU removes the page that has not been used for the longest time.



Optimal removes the page that will not be needed for the longest time in the future. It needs to know the whole reference string in advance, so it cannot be used in a real operating system. It is only a baseline to compare the other policies against.



Project structure



The code is split into small modules, one per job.



\- include and src folders hold the headers and source files.

\- replacement\_policy: base class that every policy follows.

\- fifo, lru, optimal: one file pair for each policy.

\- policy\_factory: creates a policy by type.

\- simulator: runs a policy on a reference string and counts hits and faults.

\- generators: creates random, sequential and locality-heavy reference strings.

\- working\_set: sliding-window working-set analysis.

\- main.cpp: command line program that runs the demos.



Build and run



You need a C++17 compiler such as g++.



&#x20;   g++ -std=c++17 -O2 -Iinclude src\\main.cpp src\\fifo.cpp src\\lru.cpp src\\optimal.cpp src\\policy\_factory.cpp src\\simulator.cpp src\\generators.cpp src\\working\_set.cpp -o vmsim.exe



Run the program:



&#x20;   vmsim.exe             runs everything

&#x20;   vmsim.exe compare     compares the policies for 1 to 8 frames

&#x20;   vmsim.exe belady      shows Belady's anomaly

&#x20;   vmsim.exe workingset  shows the working-set analysis





Sample output



Belady's anomaly with FIFO, using the reference string 1 2 3 4 1 2 5 1 2 3 4 5:



&#x20;   Frames  Faults

&#x20;   1       12

&#x20;   2       12

&#x20;   3       9

&#x20;   4       10

&#x20;   5       5



With 4 frames FIFO has more faults than with 3 frames. This is Belady's anomaly.



Working-set size with a window of 20 references:



&#x20;   Pattern          Average  Maximum

&#x20;   Random           12.76    17

&#x20;   Sequential       19.81    20

&#x20;   Locality-heavy   5.94     10



A smaller working set means stronger locality, so fewer frames are needed.



Results



\- Optimal never has more faults than FIFO or LRU.

\- On the sequential pattern, FIFO and LRU get no hits with 8 frames or fewer, because the loop uses 20 pages.

\- On the locality-heavy pattern with 8 frames, the hit ratio is 87.5 percent for FIFO, 88.9 percent for LRU and 92.5 percent for Optimal.



