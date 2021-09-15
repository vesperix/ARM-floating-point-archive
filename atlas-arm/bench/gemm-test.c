#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>

#include <cblas.h>

int test_sgemm(int istart,int iend,int iinc);
int test_dgemm(int istart,int iend,int iinc);
int test_cgemm(int istart,int iend,int iinc);
int test_zgemm(int istart,int iend,int iinc);
double uniform_random(void);
inline double timer(void);

int main(void)
{
  int istart = 20, iend = 2000, iinc = 20;
  printf("SGEMM:\n");
  test_sgemm(istart,iend,iinc);
  printf("\n");
  printf("DGEMM:\n");
  test_dgemm(istart,iend,iinc);
  printf("\n");
  printf("CGEMM:\n");
  test_cgemm(istart,iend,iinc);
  printf("\n");
  printf("ZGEMM:\n");
  test_zgemm(istart,iend,iinc);
}

int test_sgemm(int istart,int iend,int iinc)
{
  float *a,*b,*c,alpha,beta;
  double flops,time,n3;
  int n,i,j,nval,nits;
  double t0,t1;

  for(n=istart;n<=iend;n+=iinc) {
    nval = n * n;
    a = malloc(nval * sizeof(float));
    b = malloc(nval * sizeof(float));
    c = malloc(nval * sizeof(float));
    if(!a || !b || !c) {
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

      for(i=0;i<nval;i++) {
        a[i] = uniform_random();
        b[i] = uniform_random();
        c[i] = uniform_random();
      }
      alpha = uniform_random();
      beta = uniform_random();


      t0 = timer();

      cblas_sgemm(CblasColMajor,CblasNoTrans,CblasNoTrans,n,n,n,alpha,a,n,b,n,beta,c,n);

      t1 = timer();

      flops += 2.0 * n3;

      time += t1 - t0;
    }
    printf(" %10i %10.3e\n",n,flops / time);

    free(a);
    free(b);
    free(c);
  }
  return 0;
}

int test_cgemm(int istart,int iend,int iinc)
{
  float *a,*b,*c,alpha[2],beta[2];
  double flops,time,n3;
  int n,i,j,nval,nits;
  double t0,t1;

  for(n=istart;n<=iend;n+=iinc) {
    nval = 2 * n * n;
    a = malloc(nval * sizeof(float));
    b = malloc(nval * sizeof(float));
    c = malloc(nval * sizeof(float));
    if(!a || !b || !c) {
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

      for(i=0;i<nval;i++) {
        a[i] = uniform_random();
        b[i] = uniform_random();
        c[i] = uniform_random();
      }
      for(i=0;i<2;i++) {
        alpha[i] = uniform_random();
        beta[i] = uniform_random();
      }

      t0 = timer();

      cblas_cgemm(CblasColMajor,CblasNoTrans,CblasNoTrans,n,n,n,&alpha,a,n,b,n,&beta,c,n);

      t1 = timer();

      flops += 8.0 * n3;

      time += t1 - t0;
    }
    printf(" %10i %10.3e\n",n,flops / time);

    free(a);
    free(b);
    free(c);
  }
  return 0;
}

int test_dgemm(int istart,int iend,int iinc)
{
  double *a,*b,*c,alpha,beta;
  double flops,time,n3;
  int n,i,j,nval,nits;
  double t0,t1;

  for(n=istart;n<=iend;n+=iinc) {
    nval = n * n;
    a = malloc(nval * sizeof(double));
    b = malloc(nval * sizeof(double));
    c = malloc(nval * sizeof(double));
    if(!a || !b || !c) {
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

      for(i=0;i<nval;i++) {
        a[i] = uniform_random();
        b[i] = uniform_random();
        c[i] = uniform_random();
      }
      alpha = uniform_random();
      beta = uniform_random();

      t0 = timer();

      cblas_dgemm(CblasColMajor,CblasNoTrans,CblasNoTrans,n,n,n,alpha,a,n,b,n,beta,c,n);

      t1 = timer();

      flops += 2.0 * n3;

      time += t1 - t0;
    }
    printf(" %10i %10.3e\n",n,flops / time);

    free(a);
    free(b);
    free(c);
  }
  return 0;
}

int test_zgemm(int istart,int iend,int iinc)
{
  double *a,*b,*c,alpha[2],beta[2];
  double flops,time,n3;
  int n,i,j,nval,nits;
  double t0,t1;

  for(n=istart;n<=iend;n+=iinc) {
    nval = 2 * n * n;
    a = malloc(nval * sizeof(double));
    b = malloc(nval * sizeof(double));
    c = malloc(nval * sizeof(double));
    if(!a || !b || !c) {
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

      for(i=0;i<nval;i++) {
        a[i] = uniform_random();
        b[i] = uniform_random();
        c[i] = uniform_random();
      }
      for(i=0;i<2;i++) {
        alpha[i] = uniform_random();
        beta[i] = uniform_random();
      }

      t0 = timer();

      cblas_zgemm(CblasColMajor,CblasNoTrans,CblasNoTrans,n,n,n,&alpha,a,n,b,n,&beta,c,n);

      t1 = timer();

      flops += 8.0 * n3;

      time += t1 - t0;
    }
    printf(" %10i %10.3e\n",n,flops / time);

    free(a);
    free(b);
    free(c);
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


