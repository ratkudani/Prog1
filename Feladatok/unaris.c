#include <stdio.h>
#include <stdlib.h>

int main()
{
	int a;
	int szamlalo = 0;
	printf("Kerem adjon meg egy decimalis szamot!\n");
	scanf("%d",&a);
	printf("Unárisba valtott eredmeny:\n");
	for (int i = 0; i < a; ++i)
	{
		printf("|");
		++szamlalo;
		if (szamlalo % 5 == 0) printf(" ");
	}
	printf("\n");
	return 0;
}
