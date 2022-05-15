
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int time_diff(struct timeval *start, struct timeval *end)
{
    return ((end->tv_sec - start->tv_sec)
        * 1000 + ((end->tv_usec - start->tv_usec) / 1000));
}

int	main(void)
{
	struct timeval start; 
	struct timeval time; 
    gettimeofday(&start, NULL);
	usleep(1000000);
    gettimeofday(&time, NULL);
	printf("valeur de la latence = \n%d ", time_diff(&start, &time));
}
