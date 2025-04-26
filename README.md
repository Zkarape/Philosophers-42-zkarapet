📖 Project Overview
ft_philosophers is a 42 School project that explores the classic Dining Philosophers Problem, a famous concurrency problem invented by Edsger Dijkstra.
The goal of the project is to understand and handle multithreading, process synchronization, mutexes, and race conditions through a real-world simulation of philosophers sharing forks around a table.

The program must precisely simulate the philosophers' behavior while carefully avoiding deadlocks and data races.

🛠 Project Requirements
Only C programming language is allowed.

Use of pthread library (for mandatory part).

Use of processes and semaphores (for bonus part).

No memory leaks, deadlocks, starvation, or data races are allowed.

The code must follow 42 Norm coding style.

🎯 How It Works
Each philosopher:

Thinks 🧠

Takes the left fork 🍴

Takes the right fork 🍴

Eats 🍝

Sleeps 😴

Repeats

The simulation ends when:

A philosopher dies (has not eaten in a given time_to_die interval), or

Each philosopher has eaten at least number_of_times_each_philosopher_must_eat times (if specified).

Forks are represented by mutexes or semaphores, ensuring only one philosopher can hold a fork at a time.

🧩 Usage
1. Compilation
bash
make
This will compile the project and create the philo (mandatory) and/or philo_bonus (bonus) executables.

2. Running the Program
bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
or for the bonus version:

bash
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

Argument	Description
number_of_philosophers	Number of philosophers and forks
time_to_die	Time (in ms) until a philosopher dies without eating
time_to_eat	Time (in ms) a philosopher needs to eat
time_to_sleep	Time (in ms) a philosopher will sleep
number_of_times_each_philosopher_must_eat	(optional) Number of times each philosopher must eat before simulation ends
Example:

bash
./philo 5 800 200 200
Launches 5 philosophers where:

They die if they don't eat within 800ms.

They take 200ms to eat and 200ms to sleep.

🧠 Key Concepts
Mutexes: Used in the mandatory part to control fork access between threads.

Semaphores: Used in the bonus part for interprocess synchronization.

Threads / Processes: Each philosopher is either a thread (mandatory) or a process (bonus).

Precise timing: Careful use of usleep() and manual timestamp checks to minimize timing drift.

Death monitoring: A separate monitor ensures no philosopher is left unattended.

🏛 Project Structure
bash

✨ Bonus Part
The bonus version re-implements the simulation using processes instead of threads and semaphores for synchronization.

🚀 Key Differences:
Each philosopher is now a separate process, created using fork().

Semaphores (sem_open, sem_wait, sem_post, sem_close, sem_unlink) are used to manage forks and writing access.

Accurate process termination: when a philosopher dies, all processes must be properly terminated.

Parent process monitors children and ensures clean shutdown.

🌟 Extra Features:
Faster death detection due to independent processes.

No risk of thread-related race conditions.

⚠️ Things to Watch Out For
Deadlocks: Prevent philosophers from waiting forever for forks.

Starvation: Ensure all philosophers can eventually eat.

Timing precision: Critical to detect deaths and transitions properly.

Resource cleanup: Destroy all mutexes or semaphores at the end.

Memory leaks: None allowed, especially in the bonus version.

📚 References
Dining Philosophers Problem - Wikipedia

pthread Library Documentation

sem_open, sem_wait, sem_post Manual Pages

🧙 Author
Project by  Zhenya
42 School — ft_philosophers

