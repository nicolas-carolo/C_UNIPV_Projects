#include<stdio.h>
#include<stdlib.h>
#define N 3
int main ()
{
    int i,j;


    for (i=0;i<N;i++){
        for (j=0;j<i;j++)
        printf ("*");
        printf ("*\n");
    }

return 0;
}
