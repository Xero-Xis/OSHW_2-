#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

volatile int handler_invoked = 0; // global variable to track the number of SIGALRM signals that have been delivered
volatile int total_execution_time_seconds = 0; // global variable to track the total execution time in seconds

void handler(int signum)
{ //signal handler for SIGALRM
  handler_invoked++;
}

void int_handler(int signum)
{ //signal handler for SIGINT
  // print the total number of SIGALRM signals that have been delivered and the total execution time in seconds
  printf("Total number of SIGALRM signals delivered: %d\n", handler_invoked);
  printf("Total execution time in seconds: %d\n", total_execution_time_seconds);

  // exit the program
  exit(1);
}

int main(int argc, char * argv[])
{
  signal(SIGALRM,handler); //register handler to handle SIGALRM
  signal(SIGINT,int_handler); //register handler to handle SIGINT

  alarm(1); //Schedule a SIGALRM for 1 second

  // infinite loop
  while (1) {
    // wait for signal to be delivered
    pause();

    // handler has been invoked, so update the total execution time in seconds
    total_execution_time_seconds++;

    // reschedule SIGALRM for 1 second
    alarm(1);
  }

  return 0;
}
