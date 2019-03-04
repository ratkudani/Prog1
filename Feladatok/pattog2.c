#include<stdlib.h>
#include<time.h>
#include<stdo.h>


static void gotoxy(int x, int y)           /*kurzor pozicionálása*/
{
  int i;
  for(i=0; i<y; i++) printf("\n");          /*lefelé tolás*/
  for(i=0; i<x; i++) printf(" ");           /*jobbra tolás*/
  printf("o\n");                            /*labda ikonja*/

}

void usleep(int);
int main(void)
{
  
  int egyx=1;
  int egyy=-1;
  int i;
  int x=10;                              /*a labda kezdeti pozíciója*/
  int y=20;
  int ty[23];//magasság                  /*a pálya mérete*/
  int tx[80];//szélesség

  /*pálya széleinek meghatározása*/ 

  for(i=0; i<23; i++)
       ty[i]=1;

  ty[1]=-1;
  ty[22]=-1;

  for(i=0; i<79; i++)
       tx[i]=1;

  tx[1]=-1;
  tx[79]=-1;



  for(;;)
  {
    (void)gotoxy(x,y);
    /*printf("o\n"); Áthelyezve a gotoxy függvényve*/

    x+=egyx;
    y+=egyy;

    egyx*=tx[x];
    egyy*=ty[y];

    usleep (100000);
    (void)system("clear");
  }
}
