#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

/* Assignment #2: Scheduler */

enum status { on, off};
typedef enum status status;

enum boolean { false, true };
typedef enum boolean boolean;

unsigned short i = 0;
int pid[10];		//holds the PID for each process
status flag = on;
int numProcess = 0;	//number of process created
int current = 0;	//address of the current process
char path[256];	

struct sigaction newhandler, oldhandler;
sigset_t sig;

/*

	Non-blocking I/O function prevents read system call from waiting
	for input if none is available at time of execution.

*/
void setblock (int fd , boolean block) {

		static int blockf, nonblockf;
		static boolean first = true;

		int flags;

		if (first) {
			first = false;
			if (( flags = fcntl(fd,F_GETFL,0)) == -1) {
					fprintf(stderr," fcntl - error \n");
					exit(1);
      		}
     		blockf = flags & ~ O_NDELAY;
     		nonblockf = flags | O_NDELAY;
  		}
  		if ( fcntl(fd,F_SETFL, block ? blockf : nonblockf) == -1 ) {
				fprintf(stderr," fcntl2 - error \n");
				exit(1);
		}

}

/*

	Signal handler function switches processor from process to process.
	Checks for number of processes; if zero, it will return to the parent.

*/
void next (int code) {

    	if (numProcess!=0) {
			kill(pid[current],SIGSTOP);
			current++;
			if(current == numProcess) current = 0;
			kill(pid[current],SIGCONT);
    	}
}


int main (void) {

		char mess[80]; //user input message stored in this array
		int fd;
    	int numch;

        fd = open("/dev/tty",O_RDWR);
        setblock(fd,false);

        sigemptyset(&sig);  /* clear the signal mask */
        newhandler.sa_handler = next;  /*go to the next() function*/
        newhandler.sa_mask = sig;
        newhandler.sa_flags = 0;

        if ( sigaction(SIGALRM,&newhandler,&oldhandler) == -1 ) {
            	printf("1 - can't install signal handler \n");
            	exit(-1);
        }
        while (1) {
        	alarm(3);
        	pause();
        	switch  ( numch = read(fd,mess,80)) {
        		case -1 :
        		case  0 : break;
          		default : mess[numch-1] = '\0';  //put null character at end of string
	          			  //fprintf(stderr," %d   <%s>\n",numch,mess);
            			  pid[i] = fork();
            			  if ( pid[i] == 0 ) {				
							  strcpy(path,"./");
							  strcat(path,mess);
							  execl(path,mess,NULL);
             			  } 
						  else { 
		 					  i++; 
		 					  numProcess++;
	       				  }
            }
            fprintf(stderr,"This is the parent process.\n");
			fprintf(stderr,"Enter process name to execute.\n\n");
        }

}