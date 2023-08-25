# Dining Philosophers Problem: A README

## Introduction

The Dining Philosophers problem is a classical computer science problem for understanding concurrency, synchronization, and deadlock issues. In this simulation, philosophers either eat, think, or sleep and are positioned around a circular table filled with a large bowl of spaghetti. The simulation aims to prevent philosophers from starving or dying, using threads and mutexes for the mandatory part, and processes and semaphores for the bonus part.

---

## What I've Created

### Mandatory Part
- Program Name: `philo`
- Language: C
- Directory Structure: `philo/`
- Files: `Makefile, *.h, *.c`
- Arguments: `number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`
  
For the mandatory part, I implemented a multi-threaded program where each philosopher is represented by a separate thread. Forks are protected by mutexes to ensure that each philosopher can only use the forks adjacent to them.

### Bonus Part
- Program Name: `philo_bonus`
- Directory Structure: `philo_bonus/`
- Files: `Makefile, *.h, *.c`

For the bonus part, each philosopher is implemented as a separate process and semaphores are used to represent the forks.

---

## What I've Learned

### Thread Synchronization
The use of mutexes and threads to represent philosophers and forks provided me with a deeper understanding of thread synchronization techniques.

### Process Synchronization
The bonus part of the project helped me understand how to synchronize processes using semaphores.

### Deadlock Avoidance
The project helped me understand the fundamental problems that can lead to deadlocks and how to design algorithms to avoid them.

### Resource Allocation Strategies
I learned different strategies for resource allocation and how to ensure that all philosophers get equal access to resources, i.e., the forks in this case.

### Time Management
The use of time-based arguments like `time_to_die`, `time_to_eat`, and `time_to_sleep` helped me in learning how to manage time in a multi-threaded environment.

### Logging and Monitoring
Implementing logs for state changes in philosophers enhanced my skills in debugging and monitoring concurrent systems.

### Data Races
Ensuring the absence of data races was crucial for the integrity of the simulation, reinforcing my understanding of the importance of atomic operations.
