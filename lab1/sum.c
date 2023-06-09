// blank benchmark template

// compile with: gcc -Wall -O2 sum.c -o sum -DN=100000 -DR=100
// check assembly output: gcc -Wall -O2 sum.c -S -DN=100000 -DR=100



#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void get_walltime(double *wct) {
  struct timeval tp;
  gettimeofday(&tp,NULL);
  *wct = (double)(tp.tv_sec+tp.tv_usec/1000000.0);
}




int main() {
  double ts,te;
  double *a;
  
  // 1. allocate array
  a = (double *)malloc(N*N*sizeof(double));
  if (a==NULL) {
    printf("Allocation failed!\n");
    exit(1);
  }	  
  
  // 2. init array to 1..N
  for (int i=0;i<N*N;i++) {
    a[i] = i+1;
  }


  // get starting time (double, seconds) 
  get_walltime(&ts);
  
  // 3. reduce array to sum (R times)
  double sum = 0;
  for (int i=0;i<N;i++) {
    for (int j=0;j<N;j++) {
      sum += a[i*N+j];
    }
  }
  
  // get ending time
  get_walltime(&te);
  
  // 4. check result
  double result = (((double)N*N*(N*N+1))/2);  
  if (sum!=result) {
    printf("Reduction error!\n");
  }  
  // 5. free array
  free(a);

  printf("Execution Time (sec) = %f\n",te-ts);
  printf("MAcc/sec= = %f\n",((N*N)/((te-ts)*1e6)));
  
  
  return 0;
}
