# Mysh - Simple Shell

A simple Unix shell written in C while learning how processes, `fork()`, `execvp()`, and `waitpid()` work.

## Features

* Read commands from standard input
* Split commands into arguments
* Execute programs using `execvp()`
* Create child processes using `fork()`
* Wait for child processes using `waitpid()`
* Basic `exit` command

Example:

```text
$ ls -lah
$ pwd
$ echo Hello
$ exit
```

## Concepts

This project is mainly for learning:

* `fgets()` — read user input
* `strtok()` — split input into arguments
* `fork()` — create a child process
* `execvp()` — run a program in the child
* `waitpid()` — wait for the child process
* Process IDs (PIDs)
* Parent and child processes

## Status

Work in progress. More shell features will be added as I learn about Unix processes and system calls.
