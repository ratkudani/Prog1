#include <stdio.h>
#include <unistd.h>
#include <omp.h>

/*
int main()
{

#pragma omp parallel
	{
		for(;;);
	}
return 0;


}

Ez a végtelen ciklus, ami az összes mag 100%-os kihasználásához kell.
A futtatása a következő féleképpen zajlik : gcc program.c -o program -fopenmp */

/*
int main()
{

for (;;)
	sleep(1) ;

return 0;

}

//Ez a végtelen ciklus, az egy maghoz szükséges altatáshoz, azaz 0%-os kihasználásához.*/

int main()
{
	int i = 1;
do {
	i = i+0;
	} while(i < 2);

	return 0;
}

//Ez a végtelen ciklus, az egy maghoz való teljes, azaz 100%-os kihasználásához.