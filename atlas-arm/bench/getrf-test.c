#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>

#include <clapack.h>

int test_sgetrf(int istart,int iend,int iinc);
int test_dgetrf(int istart,int iend,int iinc);
int test_cgetrf(int istart,int iend,int iinc);
int test_zgetrf(int istart,int iend,int iinc);
double uniform_random(void);
inline double timer(void);

int main(void)
{
  int istart = 20, iend = 2000, iinc = 20;
  printf("SGETRF:\n");
  test_sgetrf(istart,iend,iinc);
  printf("\n");
  printf("DGETRF:\n");
  test_dgetrf(istart,iend,iinc);
  printf("\n");
  printf("CGETRF:\n");
  test_cgetrf(istart,iend,iinc);
  printf("\n");
  printf("ZGETRF:\n");
  test_zgetrf(istart,iend,iinc);
}

int test_sgetrf(int istart,int iend,int iinc)
{
  float *a;
  double flops,time,n3;
  int n,i,j,nval,nits,*ipiv;
  double t0,t1;

  for(n=istart;n<=iend;n+=iinc) {
    nval = n * n;
    a = malloc(nval * sizeof(float));
    ipiv = malloc(n * sizeof(int));
    if(!a || !ipiv) {
      fprintf(stderr,"Cannot allocate memory.\n");
      exit(-1);
    }

    n3 = pow(n,3);

    time = 0.0;
    flops = 0.0;

    nits = 1.0e9 / n3;

    if(nits < 3)
      nits = 3;
    if(nits > 1000)
      nits = 1000;
    
    for(j=0;j<nits;j++) {

      for(i=0;i<nval;i++)
        a[i] = uniform_random();

      t0 = timer();

      clapack_sgetrf(CblasColMajor,n,n,a,n,ipiv);

      t1 = timer();

      flops += 2.0 / 3.0 * n3;

      time += t1 - t0;
    }
    printf(" %10i %10.3e\n",n,flops / time);

    free(a);
    free(ipiv);
  }
  return 0;
}

int test_cgetrf(int istart,int iend,int iinc)
{
  float *a;
  double flops,time,n3;
  int n,i,j,nval,nits,*ipiv;
  double t0,t1;

  for(n=istart;n<=iend;n+=iinc) {
    nval = 2 * n * n;
    a = malloc(nval * sizeof(float));
    ipiv = malloc(n * sizeof(int));
    if(!a || !ipiv) {
      fprintf(stderr,"Cannot allocate memory.\n");
      exit(-1);
    }

    n3 = pow(n,3);

    time = 0.0;
    flops = 0.0;

    nits = 1.0e9 / n3;

    if(nits < 3)
      nits = 3;
    if(nits > 1000)
      nits = 1000;
    
    for(j=0;j<nits;j++) {

      for(i=0;i<nval;i++)
        a[i] = uniform_random();

      t0 = timer();

      clapack_cgetrf(CblasColMajor,n,n,a,n,ipiv);

      t1 = timer();

      flops += 8.0 / 3.0 * n3;

      time += t1 - t0;
    }
    printf(" %10i %10.3e\n",n,flops / time);

    free(a);
    free(ipiv);
  }
  return 0;
}

int test_dgetrf(int istart,int iend,int iinc)
{
  double *a;
  double flops,time,n3;
  int n,i,j,nval,nits,*ipiv;
  double t0,t1;

  for(n=istart;n<=iend;n+=iinc) {
    nval = n * n;
    a = malloc(nval * sizeof(double));
    ipiv = malloc(n * sizeof(int));
    if(!a || !ipiv) {
      fprintf(stderr,"Cannot allocate memory.\n");
      exit(-1);
    }

    n3 = pow(n,3);

    time = 0.0;
    flops = 0.0;

    nits = 1.0e9 / n3;

    if(nits < 3)
      nits = 3;
    if(nits > 1000)
      nits = 1000;
    
    for(j=0;j<nits;j++) {

      for(i=0;i<nval;i++)
        a[i] = uniform_random();

      t0 = timer();

      clapack_dgetrf(CblasColMajor,n,n,a,n,ipiv);

      t1 = timer();

      flops += 2.0 / 3.0 * n3;

      time += t1 - t0;
    }
    printf(" %10i %10.3e\n",n,flops / time);

    free(a);
    free(ipiv);
  }
  return 0;
}

int test_zgetrf(int istart,int iend,int iinc)
{
  double *a;
  double flops,time,n3;
  int n,i,j,nval,nits,*ipiv;
  double t0,t1;

  for(n=istart;n<=iend;n+=iinc) {
    nval = 2 * n * n;
    a = malloc(nval * sizeof(double));
    ipiv = malloc(n * sizeof(int));
    if(!a || !ipiv) {
      fprintf(stderr,"Cannot allocate memory.\n");
      exit(-1);
    }

    n3 = pow(n,3);

    time = 0.0;
    flops = 0.0;

    nits = 1.0e9 / n3;

    if(nits < 3)
      nits = 3;
    if(nits > 1000)
      nits = 1000;
    
    for(j=0;j<nits;j++) {

      for(i=0;i<nval;i++)
        a[i] = uniform_random();

      t0 = timer();

      clapack_zgetrf(CblasColMajor,n,n,a,n,ipiv);

      t1 = timer();

      flops += 8.0 / 3.0 * n3;

      time += t1 - t0;
    }
    printf(" %10i %10.3e\n",n,flops / time);

    free(a);
    free(ipiv);
  }
  return 0;
}

double uniform_random(void)
{
 return 2.0 * ((double)rand() / (double)RAND_MAX - 0.5);
}

inline double timer(void)
{
  struct timeval t;
  gettimeofday(&t,0);
  return (double)t.tv_sec + 1.0e-6 * t.tv_usec;
}


