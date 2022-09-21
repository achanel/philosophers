# Philosophers

Philosophers — это программа, которая визуализирует обедающих философов с журналами состояния в терминале.
В информатике проблема обедающих философов является примером проблемы, часто используемой для иллюстрации проблем синхронизации и методов их решения.

# SUMMARY

- [x] Mandatory part

• Each philosopher should be a thread.

• There is one fork between each pair of philosophers. Therefore, if there are several
philosophers, each philosopher has a fork on their left side and a fork on their right
side. If there is only one philosopher, there should be only one fork on the table.

• To prevent philosophers from duplicating forks, you should protect the forks state
with a mutex for each of them.

- [x] Bonus part

• All the forks are put in the middle of the table.

• They have no states in memory but the number of available forks is represented by
a semaphore.

• Each philosopher should be a process. But the main process should not be a
philosopher.

# Goals

* Introducing the problem of deadlock
* Understand the difference between threads and processes
* Learn about mutexes and semaphores

# RUN
- [x] Mandatory part
```bash
cd philo && make && ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <number_of_times_each_philosopher_must_eat>
```

- [x] Bonus part
```bash
cd philo_bonus && make && ./philo_bonus <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <number_of_times_each_philosopher_must_eat>
```



# Resources

* [Philosophers visualiser](https://nafuka11.github.io/philosophers-visualizer/)