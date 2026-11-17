# CPU Process Scheduling Simulator (Round Robin Queue)

A simple, console-based CPU process scheduling simulator implemented in C. This project demonstrates the **Round Robin** scheduling algorithm using a standard FIFO queue approach to manage process execution order and calculate waiting and turnaround times.

## Features
- Dynamic process input (Arrival Time & Burst Time).
- Configurable Time Quantum.
- Step-by-step execution timeline (Gantt chart output).
- Detailed summary table with average waiting and turnaround times.

## How to Compile and Run

1. Make sure you have a C compiler installed (like GCC).
2. Open your terminal or command prompt and compile the program:
   ```bash
   gcc scheduler.c -o scheduler
