#include <stdio.h>
#include <stdlib.h>

int main()
{
	
	printf("Adj meg két számot!\n");
	double x;
	double y;
	scanf("%d",&x);
	scanf("%d",&y);
	printf("\n A két általad adott szám felcserélve:\n");	
	
	x = x - y;
	y = y + x;
	x = y - x;

	printf("%d",x);
	printf("\n");
	printf("%d",y);
	printf("\n");
}
