# Philosophers

The **Philosophers** project is part of the 42 Network curriculum and is based on the classic **Dining Philosophers** problem. This project explores concurrency, multithreading, and synchronization, simulating philosophers alternately thinking, eating, and sleeping while sharing limited resources (forks).

---

## Table of Contents
- [Introduction](#introduction)
- [Problem Description](#problem-description)
- [Features](#features)
- [Usage](#usage)
- [Installation](#installation)
- [Implementation Details](#implementation-details)
- [Learning Outcomes](#learning-outcomes)
- [Credits](#credits)

---

## Introduction
The **Philosophers** project focuses on understanding and solving issues related to concurrency and synchronization in a multithreaded environment. Each philosopher is represented by a thread, and forks are shared resources protected by mutexes.

This project strengthens your ability to:
- Manage threads.
- Avoid deadlocks and race conditions.
- Optimize resource usage in concurrent systems.

---

## Problem Description
Five philosophers sit around a circular table with one fork between each pair of philosophers. They alternate between thinking, eating, and sleeping. A philosopher needs two forks (one on their left and one on their right) to eat.

### Simulation Rules:
1. Philosophers can only pick up one fork at a time.
2. A philosopher must eat before the "time to die" elapses.
3. After eating, philosophers put down their forks and start sleeping, followed by thinking.
4. The simulation ends when one philosopher dies or all have eaten the required number of meals (if specified).

---

## Features
- Handles multithreading to simulate philosophers.
- Protects shared resources (forks) using mutexes.
- Implements strategies to avoid deadlocks and starvation.
- Configurable simulation parameters:
  - Number of philosophers.
  - Time to die.
  - Time to eat.
  - Time to sleep.
  - (Optional) Number of meals each philosopher must eat.

---

## Usage

### Example Command:
```bash
./philosophers 5 800 200 200
```
This simulates 5 philosophers with:
- 800 milliseconds before a philosopher dies without eating.
- 200 milliseconds to eat.
- 200 milliseconds to sleep.

### Input Parameters:
1. `number_of_philosophers`: Total philosophers (and forks).
2. `time_to_die`: Maximum time (in ms) a philosopher can go without eating.
3. `time_to_eat`: Time (in ms) a philosopher spends eating.
4. `time_to_sleep`: Time (in ms) a philosopher spends sleeping.
5. `number_of_times_each_philosopher_must_eat` (optional): Simulation ends when all philosophers eat this many times.

---

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/philosophers.git
   cd philosophers
   ```

2. Compile the program:
   ```bash
   make
   ```

3. Run the simulation:
   ```bash
   ./philosophers <parameters>
   ```

---

## Implementation Details

### Key Concepts:
- **Threads:** Each philosopher is represented by a thread, allowing concurrent execution.
- **Mutexes:** Protect forks (shared resources) to ensure safe access.
- **Deadlock Avoidance:** Strategies like ordered resource acquisition prevent circular waiting.
- **Starvation Prevention:** Ensures fair access to resources by monitoring usage.

### Challenges Solved:
- Handling race conditions and debugging concurrency issues.
- Ensuring philosophers do not die prematurely due to resource starvation.
- Maintaining performance while avoiding bottlenecks.

---

## Learning Outcomes
Through this project, I:
- Gained hands-on experience with multithreading using pthreads.
- Learned to use mutexes for resource synchronization.
- Understood the challenges of designing concurrent systems.
- Improved problem-solving skills in deadlock and race condition scenarios.

---

## Credits

Project completed as part of the 42 Network curriculum.

---

