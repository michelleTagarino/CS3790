# Finding Primes Using Threads (Java)

This program reads two integers, **M** and **N**, where **M < N**. It spawns M threads to look for prime numbers within the given range [1...N]. Each thread is assigned an interval range computed by N/M.

## Try it Yourself!

#### To build:
	
$ make default

#### To run:
	
$ java Threads **N (range 1...N)** **M # of threads**