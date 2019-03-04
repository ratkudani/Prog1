#include <stdio.h>
#include <stdlib.h>

int main()
{
	
	printf("Adj meg két valós számot!\n");
	double a;
	double b;
	scanf("%d",&a);
	scanf("%d",&b);
	printf("\n Az általad megadott számok felcserélve:\n");	
	
	a = a + b; //a = a + b
	b = a - b; //b = (a + b) - b = a
	a = a - b; //a = (a + b) - a = b

	printf("%d",a);
	printf("\n");
	printf("%d",b);
	printf("\n");
}
