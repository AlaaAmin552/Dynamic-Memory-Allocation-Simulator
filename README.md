# Memory Allocation Simulation – Operating Systems Project  

This repository contains a fully functional simulation of memory allocation strategies used in operating systems. The project was developed as part of our coursework in Operating Systems, aiming to provide both a practical and conceptual understanding of how memory is managed in real systems.

The idea of this simulation emerged from our curiosity about how real-world operating systems handle the challenge of allocating memory to multiple processes at runtime. While studying from books gave us the theoretical background, we realized that building something tangible would greatly strengthen our understanding.

In real systems, when a program starts, it needs a portion of memory to operate. This memory has to be managed dynamically and efficiently. Over time, with many programs being loaded and unloaded, gaps start forming between memory blocks—this is known as **fragmentation**. If not handled properly, it can prevent new programs from being loaded even when there is technically enough memory available.

Through this project, we not only simulated the basic behavior of memory allocation but also observed the issues that come with it, such as **external fragmentation**, and implemented real strategies like **compaction** to solve them. This simulation served as a practical lab experience that helped us bridge the gap between abstract OS concepts and their application.

The project also provided us with a valuable team experience, where we divided roles, discussed logic structures, tested various edge cases, and ensured the code is clean, understandable, and well-commented.



## Table of Contents

- [Overview](#overview)
- [Objectives](#objectives)
- [How the Simulation Works](#how-the-simulation-works)
- [Execution Scenario](#execution-scenario)
- [Code Structure](#code-structure)
- [Team Members](#team-members)



## Overview

Memory management is one of the most crucial aspects of an operating system. As programs run, they need access to memory for data, code, and runtime information. If memory is not managed efficiently, the system performance can degrade or even crash.

This simulation mimics a real-world situation where multiple processes are created, executed, and terminated. It uses the First Fit allocation method, which assigns a new process to the first suitable space in memory. Over time, this leads to fragmentation. The simulation also implements memory compaction, which helps defragment memory and reclaim large continuous blocks.



## Objectives

- Develop a dynamic memory management simulator using C.
- Demonstrate the First Fit memory allocation strategy.
- Show how fragmentation occurs when memory is released.
- Implement memory compaction as a recovery strategy.
- Reflect on real operating system behavior using simplified logic.
- Practice team-based collaborative development.



## How the Simulation Works

The simulation begins by initializing a memory allocator with a fixed size (1000 bytes). It then runs through a sequence of memory operations that mimic a real workload.

Each process requests a specific amount of memory. When memory is allocated, it's marked with a process ID. When a process is terminated, its memory becomes free, possibly leading to scattered free blocks across memory (external fragmentation).

To resolve this, the simulation includes a **compaction** function that shifts all allocated blocks to the beginning of memory and merges all free space into a single block. This mimics the compaction feature found in actual operating systems.



## Execution Scenario

Below is the exact sequence performed when the code runs:

1. **Initialization:** Memory is initialized to 1000 bytes.
2. **Process Allocation:**
   - Process 1 is allocated 200 bytes.
   - Process 2 is allocated 350 bytes.
   - Process 3 is allocated 100 bytes.
3. **Deallocation:** Process 2 is removed, leaving a 350-byte hole in the middle.
4. **Fragmentation Test:** A new process (requires 400 bytes) tries to allocate but fails due to fragmentation.
5. **Compaction:** Memory is compacted, moving Process 1 and 3 together and freeing up a contiguous space.
6. **Re-Allocation:** The same 400-byte process is now successfully allocated after compaction.

This scenario was chosen carefully to highlight how fragmentation can occur even when enough total memory is available, and how compaction helps resolve it.



## Code Structure

- `MemoryBlock`: A structure that represents a block in memory.
- `MemoryAllocator`: Manages the entire memory as a linked list of blocks.
- `allocateMemory`: Implements First Fit allocation.
- `freeMemory`: Frees memory for a process and merges adjacent free blocks.
- `compactMemory`: Rearranges blocks to eliminate fragmentation.
- `printMemoryState`: Visualizes the current memory layout.
- `main`: Demonstrates a real sequence of operations including failure and recovery.

The code is modular, cleanly structured, and easy to extend with more strategies like Best Fit or Worst Fit if desired.


## Team Members

- **A'laa Amin Abdulaziz Elgezery**  
- **Habiba Abo Khalil Hadaad Abo Amna**  
- **Salma Mahmoud**
- **Rania Ahmed Antar** 

We worked together throughout the entire project—from brainstorming and planning to writing and testing the final implementation. Every member contributed to coding, debugging, and documentation. The result is a reliable, informative, and elegant simulation that reflects a deep understanding of memory management in operating systems.

