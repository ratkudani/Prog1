#include <stdio.h>

int main()
{
    int a;
    int b;
    printf("a értéke: ");
    scanf("%d",&a);
    printf("b értéke: ");
    scanf("%d",&b);
    printf("exor csere\n");
    a ^= b;
    b = a^b;
    a = a^b;
    printf("a új értéke: ");
    printf("%d",a);
    printf("\nb új értéke: ");
    printf("%d\n",b);
    printf("csere összeadás/kivonás\n");
    a += b;
    b = a-b;
    a = a-b;
    printf("a új értéke: ");
    printf("%d",a);
    printf("\nb új értéke: ");
    printf("%d\n",b);
    printf("csere szorzás/osztás\n");
    a *= b;
    b = a/b;
    a= a/b;
    printf("a új értéke: ");
    printf("%d",a);
    printf("\nb új értéke: ");
    printf("%d\n",b);
    
    return 0;
}
