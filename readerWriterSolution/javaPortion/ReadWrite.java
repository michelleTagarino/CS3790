/* Assignment #3: Reader/writer solution using threads and semaphores in Java */

import java.util.*;
import java.lang.Thread;
import java.util.concurrent.Semaphore;
import java.io.*;

class Reader extends Thread {
	
	private Semaphore x, wsem;
	static int readCount = 0;
	private int id;
	private PrintStream msg;

	public Reader (Semaphore x, Semaphore wsem, int id, PrintStream msg) {
		this.x = x;
		this.wsem = wsem;
		this.id = id;
		this.msg = msg;
	}

	public void run() {

		msg.printf("Reader %1d trying to access data\n", id);	

		try {
			x.acquire();
		} catch (Exception xNeg) {}		
		readCount++;		
		if (readCount == 1) {
			try {
				wsem.acquire();
			} catch (Exception wsemNeg) {}
		}
		x.release();
		msg.printf("Reader %1d is reading\n", id);
		try {
			sleep((long)(Math.random() * 1000));
		} catch (Exception e) {}
		msg.printf("Reader %1d is done reading\n", id);
		try {
			x.acquire();
		} catch (Exception xNeg) {}
		readCount--;
		if (readCount == 0) wsem.release();
		x.release();
	}
}

class Writer extends Thread {
	
	private Semaphore wsem;
	private int id;
	private PrintStream msg;

	public Writer (Semaphore wsem, int id, PrintStream msg) {
		this.wsem = wsem;
		this.id = id;
		this.msg = msg;
	}

	public void run() {
		
		msg.printf("Writer %1d is trying to write\n", id);
		try {
			sleep((long)(Math.random() * 1000));
		} catch (Exception e) {}
		try {
			wsem.acquire();
		} catch (Exception wsemNeg) {}
		msg.printf("Writer %1d is writing\n", id);
		try {
			sleep((long)(Math.random() * 1000));
		} catch (Exception e) {}
		msg.printf("Writer %1d is done writing\n", id);
		wsem.release();
		msg.printf("Writer %1d is wrapping things up\n", id);
	}

}

public class ReadWrite extends Object {

	public static void main (String [] args) {
		int rn = 0; //reader ID
		int wn = 0; //writer ID
		final int MAX = 10;

		Semaphore writeBlock = new Semaphore (1, true);
		Semaphore mutex = new Semaphore (1, true);
		
		for ( int i = 0; i < MAX; i++) {
      		if ( i % 2 == 1 ) 
          		new Reader(mutex,writeBlock,rn++,System.out).start();
      		else  new Writer(writeBlock,wn++,System.out).start(); 
    	}  
    }
}
