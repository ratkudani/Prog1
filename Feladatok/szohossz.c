#include<stdio.h>

int main(void)
{
    int h = 0;
    int n = 0x01;
    do{
    ++h;
    } while(n<<=1);
    printf("the wordlenght on this computer is ");
    printf("%d",h);
    printf(" bites\n");
    return 0;

}