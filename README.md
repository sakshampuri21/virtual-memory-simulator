# Virtual Memory and Page Replacement Simulator

## About

A modular C++ simulator that tracks page faults and hits for **1–8 configurable memory frames**. It compares three page replacement policies — FIFO, LRU, and Optimal — across different memory access patterns.

## Features

- Implements FIFO, LRU, and Optimal page replacement policies.
- Compares policies on random, sequential, and locality-heavy access patterns using fault rates and hit ratios.
- Demonstrates **Belady's anomaly** under FIFO, where increasing the number of frames can increase page faults.
- Uses a sliding-window working-set model to measure temporal locality in memory references.

## Page Replacement Policies

| Policy | Description |
|---|---|
| **FIFO** | Replaces the page that has been in memory the longest. |
| **LRU** | Replaces the page that has not been used for the longest time. |
| **Optimal** | Replaces the page whose next use is farthest in the future. Requires the complete reference string, so it serves as a theoretical baseline rather than a practical OS policy. |

## Project Structure

| File / Module | Responsibility |
|---|---|
| `include/` and `src/` | Header files and source files |
| `replacement_policy` | Base class interface for all replacement policies |
| `fifo` | FIFO policy implementation |
| `lru` | LRU policy implementation |
| `optimal` | Optimal policy implementation |
| `policy_factory` | Creates a policy based on its type |
| `simulator` | Simulates page references and counts hits and faults |
| `generators` | Generates random, sequential, and locality-heavy reference strings |
| `working_set` | Performs sliding-window working-set analysis |
| `main.cpp` | Command-line interface for running simulations |

## Build and Run

**Requirements:** C++17-compatible compiler such as `g++`.

### Compile

```bash
g++ -std=c++17 -O2 -Iinclude src/main.cpp src/fifo.cpp src/lru.cpp src/optimal.cpp src/policy_factory.cpp src/simulator.cpp src/generators.cpp src/working_set.cpp -o vmsim.exe
```

### Run

| Command | Description |
|---|---|
| `vmsim.exe` | Runs all demonstrations |
| `vmsim.exe compare` | Compares policies for 1–8 frames |
| `vmsim.exe belady` | Demonstrates Belady's anomaly |
| `vmsim.exe workingset` | Runs working-set analysis |

## Sample Results

### 1. Belady's Anomaly

Reference string: `1 2 3 4 1 2 5 1 2 3 4 5`

| Memory Frames | Page Faults |
|---:|---:|
| 1 | 12 |
| 2 | 12 |
| 3 | 9 |
| 4 | 10 |
| 5 | 5 |

With **4 frames**, FIFO produces more page faults than with 3 frames, demonstrating Belady's anomaly.

### 2. Working-Set Analysis

Window size: `20` references

| Access Pattern | Average Working-Set Size | Maximum Working-Set Size |
|---|---:|---:|
| Random | 12.76 | 17 |
| Sequential | 19.81 | 20 |
| Locality-heavy | 5.94 | 10 |

A smaller working set indicates stronger temporal locality and generally means fewer frames are needed to keep frequently accessed pages in memory.

## Key Results

- **Optimal** never produces more page faults than FIFO or LRU for the same reference string and number of frames.
- **Sequential pattern:** FIFO and LRU achieve no hits with 8 frames or fewer because the loop uses 20 pages.
- **Locality-heavy pattern with 8 frames:**

| Policy | Hit Ratio |
|---|---:|
| FIFO | 87.5% |
| LRU | 88.9% |
| Optimal | 92.5% |