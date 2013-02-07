#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

double getCurrentTimeMicro()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec*1000000.0 + t.tv_usec;
}

double getCurrentTimeMili()
{
	return getCurrentTimeMicro() / 1000.0;
}

double getCurrentTimeNano()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec*1000000000.0 + t.tv_usec;
}


double getCurrentTimeSeg()
{
	return getCurrentTimeMili() / 1000.0;
}


void printTimeElapsed(double start, double stop, char* unit)
{
	double elapsed = stop - start;
	printf("Tempo Gasto: %.3f %s\n", elapsed, unit);
}

int main(void)
{
	double start1, stop1;
	double start2, stop2;
	double start3, stop3;
	double start4, stop4;

	start1=getCurrentTimeMicro();
	start2=getCurrentTimeMili();
	start3=getCurrentTimeNano();
	start4=getCurrentTimeSeg();

	sleep(5);

	stop1=getCurrentTimeMicro();
	stop2=getCurrentTimeMili();
	stop3=getCurrentTimeNano();
	stop4=getCurrentTimeSeg();

	printTimeElapsed(start3, stop3, "Nanosegundos");

	printTimeElapsed(start1, stop1, "Microsegundos");

	printTimeElapsed(start2, stop2, "Milisegundos");

	printTimeElapsed(start4, stop4, "Segundos");

	return 0;
}
