# OS1-Project
Project Overview

This project aims to implement a small but fully functional operating system kernel that supports multithreading with time-sharing. The kernel provides essential system functionalities such as memory allocation, thread management, semaphores, and time-sharing mechanisms. Additionally, it enables asynchronous context switching and preemption based on timer and keyboard interrupts.

Features

    Thread Management: Lightweight processes (threads) within a single application.

    Memory Allocation: Custom memory allocator for efficient resource management.

    Synchronization: Semaphore implementation for inter-thread communication.

    Time-Sharing: CPU scheduling with time-slicing for fair execution.

    Preemption: Asynchronous context switching triggered by interrupts (timer and keyboard).

System Architecture

      The kernel is designed as a library-based system where the application and the kernel share the same address space.

      It does not load and execute arbitrary user programs but instead runs a preloaded embedded program.

      The implementation is targeted for RISC-V processor architecture and is designed for an educational computer system with this architecture.

      The kernel is executed in a virtualized environment using a RISC-V emulator.

Implementation Details

      Programming Languages: The kernel is implemented using C/C++ and RISC-V assembly.

      Thread Model: Uses cooperative and preemptive multitasking.

      Interrupt Handling: Supports hardware timer and keyboard interrupts for context switching.

      Memory Management: Implements a simple heap allocator.

Author

      Filip Verbabic
