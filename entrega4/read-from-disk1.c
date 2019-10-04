#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>


int main(int argc, char * argv [])
{
	struct timespec ts0, ts1;
	int res;
	double secs;
	char *c;

	if (argc != 2) {
		printf("Has de passar 1 parametre\n");
		exit(0);
	}

	char *text = "8======D";
	res = clock_gettime(CLOCK_REALTIME, &ts0);

	FILE *f = fopen(argv[1], "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}
	while (read(f, &c, 8) != 0);

	res = clock_gettime(CLOCK_REALTIME, &ts1);
	
	fclose(f);

	secs = (((double)ts1.tv_sec*1000000000.0 + (double)ts1.tv_nsec) - 
          ((double)ts0.tv_sec*1000000000.0 + (double)ts0.tv_nsec))/1000000000.0;

	printf (" secs   %.8lf s. (%le s/sleep)\n", secs, secs ); 
}