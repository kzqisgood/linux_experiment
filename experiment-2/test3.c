#include <stdio.h>
int main(int argc,char *argv)

{

         int i;

         if(argc<=1)

                  printf("no para!\n");

         else

         {

                  printf("there is %d para，and the para is:\n",argc-1);

                  for(i=1;i<argc;i++)

                          printf("%d   ",argv[i]);

         }

}
