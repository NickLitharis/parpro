// Sample triad benchmark with arrays of doubles
// compile with: gcc -Wall -O2 triad-double.c -o triad-double -DN=10000 -DR=10000


#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#define BLOCKSIZE  ((N+THREADS-1)/THREADS)

// struct of info passed to each thread
struct thread_params {
  int id;		// thread's id (for demo purposes)
  double *pa,*pb,*pc,*pd;
  int n;
};

void get_walltime(double *wct) {
  struct timeval tp;
  gettimeofday(&tp,NULL);
  *wct = (double)(tp.tv_sec+tp.tv_usec/1000000.0);
}

void *thread_func(void *args) {
 
  // get arguments
  int i,j;
  struct thread_params *tp = (struct thread_params *)args;
  
  // int id = tp->id;
  int n = tp->n;
  double *pa = tp->pa;
  double *pb = tp->pb;
  double *pc = tp->pc;
  double *pd = tp->pd;
 
  // useful work here
  // do triad artificial work
  for (j=0;j<R;j++) {
    for (i=0;i<n;i++) {
      pa[i] = pb[i]*pc[i]+pd[i];
    }
  }

  // exit and let be joined
  pthread_exit(NULL);
}

int main() {
  double *a,*b,*c,*d;
  int i;
  double ts,te,mflops;
  pthread_t pid[THREADS];
  
  struct thread_params tparm[THREADS];

  // allocate test arrays
  a = (double *)malloc(N*sizeof(double));
  if (a==NULL) exit(1);
  b = (double *)malloc(N*sizeof(double));
  if (b==NULL) { free(a); exit(1); }
  c = (double *)malloc(N*sizeof(double));
  if (c==NULL) { free(a); free(b); exit(1); }
  d = (double *)malloc(N*sizeof(double));
  if (d==NULL) { free(a); free(b); free(c); exit(1); }
  
  //initialize all arrays - cache warm-up
  for (i=0;i<N;i++) {
    a[i]=2.0*i;
    b[i]=-i;
    c[i]=i+5.0;
    d[i]=-7.0*i;
  }
 
  // get starting time (double, seconds) 
  get_walltime(&ts);
  
  for (int i=0;i<THREADS;i++) {
    // fill tparm[i]
    tparm[i].id = i;
    tparm[i].pa = a+i*BLOCKSIZE;
    tparm[i].pb = b+i*BLOCKSIZE;
    tparm[i].pc = c+i*BLOCKSIZE;
    tparm[i].pd = d+i*BLOCKSIZE;

    if (i==(THREADS-1)) { // last thread, maybe less than blocksize to do
      tparm[i].n = N-i*BLOCKSIZE; 
    }
    else { 
      tparm[i].n = BLOCKSIZE; // any other thread, always blocksize work to do 
    }
      
    // create i-th thread, pass ptr to tparm[i]
    if (pthread_create(&pid[i],NULL,thread_func,&tparm[i])!=0) {
      printf("Error in thread creation!\n");
      exit(1);
    }
  }
  
  //join
  for (int i=0;i<THREADS;i++) {
    if (pthread_join(pid[i],NULL)!=0) {
      printf("Error in thread join!\n");
      exit(1);  
    }
  }
 
  // get ending time
  get_walltime(&te);
  
  // check result - avoid loop removal by compiler
   for (i=0;i<N;i++) {
    if (a[i]!=b[i]*c[i]+d[i]) {
      printf("Error!\n");
      break;
    }
  }
 
  
  // compute mflops/sec (2 floating point operations per R*N passes)
  mflops = (2.0*R*N)/((te-ts)*1e6);
  
  printf("MFLOPS/sec = %f\n",mflops);
  
  // free arrays
  free(a); free(b); free(c); free(d);
  
  return 0;
}

