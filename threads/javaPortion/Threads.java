/* Lab Assignment #2: Java Threads */

import java.util.*;
import java.lang.Thread;

class PrimeThreads implements Runnable {

    private int lowerBound; //start of thread range
    private int upperBound; //end of thread range
    private int threadID; //current thread

    public PrimeThreads(int lowerBound, int upperBound, int threadID) {
        this.lowerBound = lowerBound;
        this.upperBound = upperBound;
        this.threadID = threadID;
    }
    /*
        executes the current thread
    */
    public void run() {

        for (int i = lowerBound; i <= upperBound; i++) {
            if (isPrime(i) != 0) {
                System.out.print("\nThread " + threadID + " found: " + i);
            }
        }

    }
    /*
     	returns the number if it is prime, 0 if it is not
     */
    public int isPrime(int n) {

        if (n < 2) return 0;
        if (n == 2) return n;
        for (int i = 2; i < n; i++) {
            if (n % i == 0) return 0;
        }
        return n;

    }
}

public class Threads {
    
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        
        int n = 0; //used to find prime numbers between 1 and n
        int m = 1; //number of threads user enters
        int intervalLength; //range of each thread
        int lowerBound; //start of thread range
        int upperBound; //end of thread range

		if (args.length > 0) {
			try {
				n = Integer.parseInt(args[0]);
			} catch (NumberFormatException e) {
				System.err.println("Argument " + args[0] + " must be an int.");
				System.exit(1);
			}
			try {
				m = Integer.parseInt(args[1]);
			} catch (NumberFormatException e) {
				System.err.println("Argument " + args[0] + " must be an int.");
				System.exit(1);
			} 
		}

        intervalLength = n / m;

        Thread thrd[] = new Thread[m];
        
        for (int i = 0; i < m; i++) {
            lowerBound = (i*intervalLength) + 1;
            upperBound = (i+1) * intervalLength;
            thrd[i] = new Thread(new PrimeThreads(lowerBound, upperBound, i));
            thrd[i].start();
        }
		for (int i = 0; i < m; i++) {
			try {
                thrd[i].join();
            } catch (InterruptedException ie) {
                System.out.println("Thread " + i + " Interrupted");
            }
		}
		System.out.print("\n\n");
    }
}
