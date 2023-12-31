#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void sigint_handler (int signo)
{
	printf("Caught SIGINT!\n");
	exit(EXIT_SUCCESS);
}

void main()
{
	if(signal(SIGINT, sigint_handler) == SIG_ERR){
		fprintf (stderr, "Cannot handle SIGINT!\n");
		exit (EXIT_FAILURE);
	}
	for (;;)
		pause ();
	return ;
}
