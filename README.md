*This project has been created as part of the 42 curriculum by larchimb.*

# Codexion

## Description

Codexion is a concurrency project written in C using POSIX threads and synchronization primitives.

The simulation represents several coders working around a circular table. Each coder has a left and a right USB dongle, but compiling requires both dongles simultaneously.

The goal is to coordinate all coders efficiently while avoiding deadlocks, starvation, race conditions and burnout.

Each coder repeatedly:

1. Acquires two dongles.
2. Compiles.
3. Releases the dongles.
4. Debugs.
5. Refactors.
6. Tries to compile again.

The simulation ends when every coder has reached the required number of compilations or when a coder burns out.

## Instructions

### Compilation

```bash
make
```

Other available commands:

```bash
make clean
make fclean
make re
```

### Execution

```bash
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

The scheduler must be either:

* `fifo` — requests are handled in arrival order.
* `edf` — the coder with the earliest burnout deadline is prioritized.

### Example

```bash
./codexion 4 800 200 200 200 5 50 edf
```

## Output

State changes must follow this format:

```text
timestamp coder has taken a dongle
timestamp coder is compiling
timestamp coder is debugging
timestamp coder is refactoring
timestamp coder burned out
```

Burnout messages must be displayed within 10 ms of the actual burnout time.

Output is serialized so that messages from different threads never overlap.

## Blocking cases handled

### Deadlock prevention

Coders need two dongles at the same time. Access is synchronized to prevent inconsistent ownership and deadlocks. Only one mutex is used for all the dongles.

### Starvation prevention

The scheduler ensures that waiting coders are eventually considered. EDF prioritizes the earliest burnout deadline, while FIFO respects request order. In case of equality for EDF the program use FIFO.

### Dongle cooldown

After a dongle is released, it remains unavailable until `dongle_cooldown` milliseconds have elapsed.

### Precise burnout detection

A dedicated monitor thread checks coder deadlines and detects burnout precisely. The burnout message must be printed within 10 ms.

### Log serialization

A mutex protects the output so that two threads cannot write an interleaved message.

## Thread synchronization mechanisms

### `pthread_mutex_t`

Mutexes protect shared resources such as dongle states and logging.

For example, a coder must lock the appropriate dongle mutex before acquiring a dongle, preventing two coders from taking the same dongle simultaneously.

### `pthread_cond_t`

Condition variables can be used to put waiting coders to sleep and wake them when resources become available.

They also allow the scheduler to coordinate access to dongles without unnecessary busy waiting.

### `pthread_cond_timedwait`

Make the thread waiting on the condition define previously or according to a time.

### Monitor synchronization

The monitor thread communicates safely with coder threads through protected shared state. Mutexes ensure that coder status, deadlines and simulation termination are accessed without race conditions.

## Resources

* POSIX Threads documentation: `pthread_create`, mutexes and condition variables.
* `gettimeofday()` / `clock_gettime()` documentation for timing.
* 42 Codexion subject and evaluation requirements.

AI was used only as an assistance tool for documentation and understanding of the project requirements. Any generated information was reviewed and understood before being used.

## License

This project is part of the 42 curriculum and is intended for educational purposes.
