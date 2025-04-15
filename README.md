
# Advanced Memory Allocator Simulation
### Operating Systems Course Project

This repository contains a complete and educational simulation of memory allocation techniques used in operating systems. It is designed to illustrate various strategies of memory management, including their advantages, disadvantages, and use cases. This project not only implements the functionality of memory allocation but also explains the core logic and challenges behind memory handling.

---

## Table of Contents
- [Introduction](#introduction)
- [Objectives](#objectives)
- [Background & Concepts](#background--concepts)
- [Implemented Algorithms](#implemented-algorithms)
  - [First Fit](#first-fit)
  - [Best Fit](#best-fit)
  - [Worst Fit](#worst-fit)
- [Fragmentation](#fragmentation)
- [Memory Compaction](#memory-compaction)
- [How It Works](#how-it-works)
- [Code Overview](#code-overview)
- [Execution Flow](#execution-flow)
- [Sample Output](#sample-output)
- [Compile & Run](#compile--run)
- [Challenges](#challenges)
- [Possible Improvements](#possible-improvements)
- [Team Members](#team-members)
- [License](#license)

---

## Introduction

Memory is a limited resource in computing systems. When multiple programs run simultaneously, the operating system must manage memory efficiently to ensure performance and reliability. This simulation helps visualize how allocation strategies work and how fragmentation can occur during allocation and deallocation of memory.

---

## Objectives

- Simulate real-world memory allocation strategies.
- Implement First Fit, Best Fit, and Worst Fit methods.
- Demonstrate external fragmentation and resolution via compaction.
- Enhance understanding of operating system memory concepts.
- Encourage hands-on learning and algorithmic thinking.

---

## Background & Concepts

Memory management is responsible for tracking each byte in a computer’s memory and efficiently allocating memory blocks to processes as needed. The core responsibilities include:
- Allocation and deallocation of memory.
- Keeping track of used and free memory.
- Avoiding fragmentation.

---

## Implemented Algorithms

### First Fit

- **Description:** Allocates the first memory block large enough to fit the process.
- **Pros:** Fast and simple.
- **Cons:** Can leave small unusable holes leading to fragmentation.
- **Use Case:** Suitable for systems where speed is prioritized over efficiency.

### Best Fit

- **Description:** Allocates the smallest available block that fits the process.
- **Pros:** Minimizes wasted space.
- **Cons:** Slower due to the need to search all blocks; may create many small unusable blocks.
- **Use Case:** Efficient memory usage environments.

### Worst Fit

- **Description:** Allocates the largest available block.
- **Pros:** Leaves reasonably sized free memory blocks.
- **Cons:** Can increase fragmentation and waste.
- **Use Case:** Suitable when large allocations are expected later.

(Note: Current implementation uses **First Fit**, but the structure allows adding Best Fit and Worst Fit easily.)

---

## Fragmentation

### External Fragmentation
Occurs when enough total free memory exists to satisfy a request, but it is split into small blocks scattered throughout memory. A process needing a large contiguous block may fail to be allocated despite sufficient overall free space.

### Internal Fragmentation
Occurs when allocated memory is slightly larger than requested, leading to wasted space within allocated blocks.

---

## Memory Compaction

To solve external fragmentation, memory compaction moves all allocated processes together and merges all free space into one block. This allows future large allocations to succeed. In our simulation, compaction is a manual function triggered when needed.

---

## How It Works

- The memory is initialized as a single large free block (e.g., 100 units).
- Processes request specific memory sizes.
- Based on the chosen strategy, memory is searched for a suitable block.
- Processes can be freed (deallocated).
- If external fragmentation occurs, compaction is applied to consolidate free space.

---

## Code Overview

- `add_process(name, size)`: Adds a new process.
- `free_process(name)`: Frees memory for a process.
- `compact_memory()`: Performs memory compaction.
- `print_memory()`: Displays current memory state.
- Memory is represented as an array of `Block` structures.

---

## Execution Flow

1. Add process P1 (20 units).
2. Add process P2 (30 units).
3. Add process P3 (10 units).
4. Remove process P2 to create fragmentation.
5. Try to add process P4 (25 units) – fails due to fragmentation.
6. Perform compaction.
7. Add P4 again – succeeds.

---

## Sample Output

```
[P1] Start: 0, Size: 20, Allocated
[P2] Start: 20, Size: 30, Allocated
[P3] Start: 50, Size: 10, Allocated
[Free] Start: 60, Size: 40, Free

Removing P2...

[P1] Start: 0, Size: 20, Allocated
[Free] Start: 20, Size: 30, Free
[P3] Start: 50, Size: 10, Allocated
[Free] Start: 60, Size: 40, Free

Adding P4 (25 units) → FAILED

Compacting...

[P1] Start: 0, Size: 20, Allocated
[P3] Start: 20, Size: 10, Allocated
[Free] Start: 30, Size: 70, Free

Adding P4 (25 units) → SUCCESS
```

---

## Compile & Run

```bash
gcc memory_allocator.c -o allocator
./allocator
```

---

## Challenges

- Handling fragmentation during frequent allocations/deallocations.
- Designing a flexible and extensible memory structure.
- Keeping memory layout output clear and readable.

---

## Possible Improvements

- Implement Best Fit and Worst Fit fully.
- Add interactive menu for dynamic user input.
- Create GUI for visual simulation.
- Support merging adjacent free blocks automatically.

---

## Team Members

- آلاء أمين عبد العزيز الجزيري  
- حبيبة أبو خليل  
- رانيا أحمد عنتر  
- سلمى محمود

Each member contributed to writing code, testing the allocator, and documenting the project. We worked collaboratively to simulate real OS memory behavior.

---

## License

This repository is licensed for academic and educational use. Free to adapt for learning purposes.

---
