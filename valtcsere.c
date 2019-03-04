#include<stdio.h>

int main()
{


int a;
int b;


scanf("%d",&a);
scanf("%d",&b);
printf("\n");

a = a - b;
b = b + a;
a = b - a;

printf("%d",a);
printf("\n");
printf("%d",b);
printf("\n");




}