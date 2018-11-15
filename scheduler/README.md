# Scheduler

This program prompts the user to enter a process to execute (i.e. 'a', 'b', or 'c') in the terminal. The initial process is forked and the child process will continue to run until the user signals the **exec** call to replace the current child process with the new one (inputs new process name). The processes are executed in a Round-Robin fashion by way of the signal handler.

## Let's Get You Started
### Prerequisites
This may only work a linux machine

To build:

	$ make labass2

To run:

	$./labass2