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
	return getCurrentTimeMicro() / 1000000.0;
}


void printTimeElapsed(double start, double stop, char* unit)
{
	double elapsed = stop - start;
	printf("Tempo Gasto: %.3f %s\n", elapsed, unit);
}

int main(void)
{
    double start, stop;

    start=getCurrentTimeMicro();
    /*
    *
    *Algoritmo aqui
    *
    */
    stop=getCurrentTimeMicro();
    printTimeElapsed(start, stop, "Microsegundos");

    return 0;
}
