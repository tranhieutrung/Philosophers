# Philosophers Project
# Introduction
The Philosophers Project is a simulation of the famous dining philosophers problem, where multiple philosophers sit around a table, thinking, eating, and occasionally sleeping. The project aims to model synchronization and concurrency using threads and mutexes to manage access to shared resources (the forks). The objective is to ensure that the philosophers behave in a way that avoids deadlock or data race; and ensures that they eat a specified number of times.

The project requires careful management of shared resources, thread synchronization, and handling of different states such as eating, thinking, and sleeping. The goal is to simulate the philosophers' behavior while ensuring the system functions efficiently and without errors like deadlock or race conditions.

# Project Requirements
The program simulates n philosophers sitting at a table, each needing two forks to eat. A philosopher spends their time alternating between thinking, eating, and sleeping. The simulation should handle:

- Fork acquisition (philosophers pick up two forks before eating).
- Eating behavior (philosophers must eat for a specified amount of time).
- Sleeping behavior (philosophers sleep for a specified amount of time between eating).
- Thinking behavior (when a philosopher is neither eating nor sleeping).
- Deadlock prevention (ensure philosophers don't get stuck waiting indefinitely for forks).

# Features:
- Philosophers can be set to eat a specific number of times.
- The system can detect when a philosopher dies due to hunger.
- It tracks when all philosophers have finished eating.
- Deadlock and data-race handling and prevention via mutex locks and condition variables.

# How to Use
## Compile the Project:
```bash
git clone https://github.com/tranhieutrung/Philosophers.git
cd Philosophers
make
```

## Run the Simulation:
To run the simulation, use the following command:
```bash
./philosophers <num_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [optional: <num_of_meals>]
```
## Example:

```bash
./philosophers 5 800 200 200 3
```
![Usage GIF](https://github.com/tranhieutrung/Philosophers/blob/main/Philosophers.gif)

### In this example:

5 philosophers are simulated.<br>
Each philosopher can live for 800 milliseconds before dying.<br>
Each philosopher takes 200 milliseconds to eat and 200 milliseconds to sleep.<br>
Each philosopher must eat 3 times.<br>

# Project Execution Flow
## Initialization:
- The program begins by initializing all philosophers and the mutexes to protect shared resources.

## Simulation Loop:
- Philosophers begin their routine, alternating between thinking, grabbing forks, eating, and sleeping.
- A monitor thread continuously checks if a philosopher has died (i.e., has not eaten in a specified amount of time).

## Thread Management:

- Each philosopher runs in its own thread.
- Forks are shared between two adjacent philosophers, protected by mutexes to prevent simultaneous access and ensure the system remains deadlock-free.
- All philosophers start by "thinking," then even-numbered philosophers will begin by taking forks and eating, while odd-numbered philosophers will wait until the even-numbered ones finish eating and return the forks before they can start taking their forks and eating.
- In the simulation with an even number of philosophers, one philosopher (the last one, n-1) will have to wait twice before they can eat.

## Error Handling:

- The program ensures that no deadlocks occur and that philosophers do not wait indefinitely for forks.
- The program also gracefully handles errors during the creation of threads, mutex locking, and other critical operations.
# Result:
100% completion rate, with full implementation of mandatory features 🎉
![Result](https://github.com/tranhieutrung/Philosophers/blob/main/Philosophers_result.png)
# Conclusion
This project demonstrates how to solve concurrency problems using threads and mutexes. It simulates the classic dining philosophers problem with a focus on preventing deadlock and ensuring that philosophers can eat their required number of times. By using synchronization primitives like mutex locks, the program ensures that the shared resources (forks) are accessed safely.