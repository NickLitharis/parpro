// this is the plain version of dot product of two NxN matrices of doubles
// compile with:  gcc -Wall -O2 mmult-double.c -o mmult-double -DN=1000


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
// how many elements a thread will process - note surrounding ()!
#define BLOCKSIZE  ((N+THREADS-1)/THREADS)

// struct of info passed to each thread
struct thread_params {
  int id;	// thread's id (for demo purposes)
  double *pa;	// start of array to work on	
  double *pb;
  double *pc;
  int n;	// how many items to process
};

void *thread_func(void *args) {
 
  // get arguments
  struct thread_params *tp = (struct thread_params *)args;
  // int id = tp->id;
  int n = tp->n;
  double *pa = tp->pa;
  double *pb = tp->pb;
  double *pc = tp->pc;
 
  // useful work here
  // load, matrix multiplication
  for (int i=0;i<n;i++) {	// for all rows of A,C
  
    for (int j=0;j<N;j++) {	// for all "columns" (rows) of B
    
      double sum = 0.0;
      for (int k=0;k<N;k++) {	// for each element of selected A row and B "column"
        sum += pa[i*n+k]*pb[j*n+k];	// a[i,k]*b[j,k]  note: B is transposed, originally b[k,j]
      }
      pc[i*N+j] = sum;	// c[i,j]
    
    }
  
  }

  // exit and let be joined
  pthread_exit(NULL);
}


void get_walltime(double *wct) {
  struct timeval tp;
  gettimeofday(&tp,NULL);
  *wct = (double)(tp.tv_sec+tp.tv_usec/1000000.0);
}


int main() {
double ts,te;
pthread_t pid[THREADS];
struct thread_params tparm[THREADS];
double *a,*b,*c;	// matrices A,B,C C=AxB, B is transposed

  a = (double *)malloc(N*N*sizeof(double));
  if (a==NULL) {
    exit(1);
  }
  
  b = (double *)malloc(N*N*sizeof(double));
  if (b==NULL) {
    free(a); exit(1);
  }

  c = (double *)malloc(N*N*sizeof(double));
  if (c==NULL) {
    free(a); free(b); exit(1);
  }

  // init input and output matrices
  for (int i=0;i<N;i++) {
    for (int j=0;j<N;j++) {
      a[i*N+j] = i;
      b[i*N+j] = i;
      c[i*N+j] = 0.0;
    }
  }

  // get starting time (double, seconds) 
  get_walltime(&ts);

  for (int i=0;i<THREADS;i++) {
    // fill tparm[i]
    tparm[i].id = i;
    tparm[i].pa = a+N*i*BLOCKSIZE;
    tparm[i].pb = b;
    tparm[i].pc = c+N*i*BLOCKSIZE;
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
  
  // block until join
  for (int i=0;i<THREADS;i++) {
    if (pthread_join(pid[i],NULL)!=0) {
      printf("Error in thread join!\n");
      exit(1);  
    }
  }

  // get ending time
  get_walltime(&te);

  // print computation time
  printf("Computation time = %f sec\n",(te-ts));

  // test result
  int done = 0;
  for (int i=0;i<N&&done==0;i++) {
    for (int j=0;j<N;j++) {
      if (c[i*N+j]!=(double)i*j*N) { printf("Error! %d,%d (%f)\n",i,j,c[i*N+j]); done=1; break; }  
    }
  }

  free(c);
  free(b);
  free(a);
  
  return 0;
}
