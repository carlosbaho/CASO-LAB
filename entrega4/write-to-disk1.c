#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>


int main(int argc, char * argv [])
{
	
	int res;
	void *p;
	struct timespec ts0, ts1;
	double secs, secs2;
	
	res = clock_gettime(CLOCK_REALTIME, &ts0);
	if (res < 0) { 
      perror ("clock_gettime");
	}	
	
	int X = 1024 * 1024 * 500*2*2;
	FILE *fp = fopen(argv[1], "w");
	fseek(fp, X , SEEK_SET);
	fputc('\0', fp);
	fclose(fp);	
	
	res = clock_gettime(CLOCK_REALTIME, &ts1);
	if (res < 0) {
      perror ("clock_gettime");
	}

	secs = (((double)ts1.tv_sec*1000000000.0 + (double)ts1.tv_nsec) - 
          ((double)ts0.tv_sec*1000000000.0 + (double)ts0.tv_nsec))/1000000000.0;       
          
    printf (" secs   %.8lf s. (%le s/sleep)\n", secs, secs );      
          
          
          
}
