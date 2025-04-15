# Advanced Memory Allocation Simulation  
### Operating Systems Course Project

This project represents a simulation designed to illustrate memory management techniques used in operating systems. The focus is on presenting the way memory allocation works in practice, especially in cases where multiple processes request space at different times and the operating system must handle these requests efficiently. The goal of this simulation is to provide a simplified but meaningful representation of how allocation strategies operate, the problems they might cause, and how certain techniques can be used to resolve those problems.

## Table of Contents

- Introduction  
- Project Goals  
- Core Concepts  
- Allocation Strategies  
- Memory Fragmentation  
- Memory Compaction  
- Simulation Workflow  
- Team Members  

## Introduction

Memory is one of the most critical resources managed by an operating system. As multiple programs and processes run simultaneously, the system needs to ensure that memory is divided and allocated in a way that avoids waste, overlap, or errors. 

The objective of this simulation is to represent, in a clear and simple manner, how different allocation strategies affect the usage of memory. It helps highlight challenges such as fragmentation and how solutions like compaction can help overcome these limitations. The project is intended to bridge the gap between theoretical concepts and their actual implementation, especially for students learning about operating systems.

## Project Goals

- To implement a memory allocation simulator that can demonstrate how memory is assigned to processes based on different strategies.  
- To build a foundation for understanding external fragmentation and its impact on overall memory utilization.  
- To introduce memory compaction as a resolution method and allow manual testing within the simulation.  
- To reinforce key operating system concepts through a hands-on project approach.  
- To keep the design modular, making it easier to build upon or modify in future versions.

## Core Concepts

Memory management is a fundamental component of operating systems. It is responsible for tracking which parts of memory are in use, which parts are free, and ensuring that active processes are provided with sufficient memory to operate.

In this simulation, memory is visualized as a sequence of blocks—each either free or allocated to a specific process. The memory manager must find a way to fit new processes into available space, handle deallocation when processes are removed, and maintain a consistent structure throughout.

This simulation particularly emphasizes two common challenges:

- Allocating space efficiently.
- Managing the free memory left behind when processes are removed.

## Allocation Strategies

### First Fit

In this strategy, the memory manager scans the memory blocks from the beginning and allocates the first block that is large enough to satisfy the requested size.  
**Advantages:** This method is quick because it does not check all the blocks—just the first suitable one.  
**Disadvantages:** It can leave small, unusable holes in memory over time, which leads to external fragmentation.  

In our implementation, First Fit is the default method used. However, the code is structured in a way that allows for other strategies to be implemented later if needed.

## Memory Fragmentation

Memory fragmentation occurs when the memory becomes inefficiently utilized due to the way processes are allocated and deallocated. There are two main types:

### External Fragmentation

This occurs when there is enough total free memory to satisfy a new process, but the available blocks are scattered and not large enough individually. This makes it impossible to allocate memory to a new process even though the total free memory might be sufficient.

## Memory Compaction

Compaction is a method used to solve the problem of external fragmentation. It involves rearranging the allocated processes to be adjacent to each other, which collects all the free memory into a single block. 

In this simulation, compaction is not automatic but can be triggered manually. When invoked, all active processes are shifted to the beginning of memory, and the remaining space is consolidated at the end.

## Simulation Workflow

- The memory starts as a single large free block.
- When a new process is added, it requests a specific size.
- The memory manager searches for a suitable block using the First Fit method.
- If space is available, the process is allocated and marked.
- If a process is removed, its block is freed and marked as available.
- In cases where memory cannot be allocated due to fragmentation, compaction can be triggered to reorganize memory and allow new allocations.

## Team Members

- A'laa Amin Abdulaziz Elgezery
- Habiba Abo Khalil Hadaad Abo Amna
- Salma Mahmoud 
- Rania Ahmed Antar

Each team member contributed to the planning, implementation, testing, and documentation of the simulation. The work was done collaboratively, with everyone sharing ideas and responsibilities to ensure the project accurately reflects memory management behavior in operating systems.
