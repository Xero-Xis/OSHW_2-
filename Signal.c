#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile int handler_invoked = 0; // global variable to communicate between the signal handler function and the main function

void handler(int signum)
{ //signal handler
  printf("Hello World!\n");
  handler_invoked = 1;
}

int main(int argc, char * argv[])
{
  signal(SIGALRM,handler); //register handler to handle SIGALRM
  alarm(1); //Schedule a SIGALRM for 1 second

  // busy wait for signal to be delivered
  while (1) {
  // wait for signal to be delivered
  pause();

  // handler has been invoked, so print "Turing was right!"
  printf("Turing was right!\n");

  // reschedule SIGALRM for 1 second
  alarm(1);
  }
  // handler has been invoked, so print "Turing was right!" and exit
  printf("Turing was right!\n");
  exit(1);
}
