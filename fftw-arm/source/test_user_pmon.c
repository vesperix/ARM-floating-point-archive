#include <stdio.h>

unsigned getticks(void)
{
     unsigned cc;
     static int init = 0;
     if(!init) {
         __asm__ __volatile__ ("mcr p15, 0, %0, c9, c12, 2" :: "r"(1<<31)); /* stop the cc */
         __asm__ __volatile__ ("mcr p15, 0, %0, c9, c12, 0" :: "r"(5));     /* initialize */
         __asm__ __volatile__ ("mcr p15, 0, %0, c9, c12, 1" :: "r"(1<<31)); /* start the cc */
         init = 1;
     }
     __asm__ __volatile__ ("mrc p15, 0, %0, c9, c13, 0" : "=r"(cc));
     return cc;
}

int main(void)
{
  int i;
  printf("Preparing to test the ARMv7a cycle counter.\n\n");
  printf("An \"illegal instruction\" error during this test indicates\n");
  printf("that the cycle counter is not available.\n\n");
  printf("If the ARMv7a cycle counter works on your system, you should now see\n");
  printf("10 different cycle counts in the right hand column below.\n");
  for(i=1;i<=10;i++) {
    printf(" %2i: %20d\n",i,getticks());
  }
  printf("ARMv7a cycle counter read test complete.\n");
  printf("To use this counter in FFTW-NEON, use the configure option\n");
  printf("  --enable-armv7a-cycle-counter\n");
}


