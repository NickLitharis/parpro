#include <stdio.h>
#include <stdlib.h>
#include <emmintrin.h>
#include <sys/time.h>

// this is the float version of dot product of two NxN matrices 
// compile with: gcc -Wall -O2 mmult-float.c -o mmult-float -DN=1000

// NOTE: in order to be cache friendly, matrix B is assumed to be transposed


void get_walltime(double *wct) {
  struct timeval tp;
  gettimeofday(&tp,NULL);
  *wct = (double)(tp.tv_sec+tp.tv_usec/1000000.0);
}


int main() {
double ts,te;
float *a,*b,*c;
__m128 *pa,*pb;
int i;
  // allocate test arrays - request alignment at 16 bytes
  i = posix_memalign((void **)&a,16,N*N*sizeof(float));
  if (i!=0) exit(1);
  i = posix_memalign((void **)&b,16,N*N*sizeof(float));
  if (i!=0) { free(a); exit(1); }
  // i = posix_memalign((void **)&c,16,N*N*sizeof(float));
  // if (i!=0) { free(b); free(a); exit(1); }
  
  // //initialize float input test arrays fa, fb
  // pa[0] = 1.0; pa[1] = 2.0; pa[2] = 3.0; pa[3] = 4.0;
  // pb[0] = 1.1; pb[1] = 2.2; pb[2] = 3.3; pb[3] = 4.4;

  // alias the sse pointers to input and output test arrays
  pa = (__m128 *)a; 
  pb = (__m128 *)b;
  // vfc = (__m128 *)pc;

  // a = (float *)malloc(N*N*sizeof(float));
  // if (a==NULL) {
  //   printf("Allocation failed!\n");
  //   exit(1);
  // }
  
  // b = (float *)malloc(N*N*sizeof(float));
  // if (b==NULL) {
  //   printf("Allocation failed!\n");
  //   free(a); exit(1);
  // }

  c = (float *)malloc(N*N*sizeof(float));
  if (c==NULL) {
    printf("Allocation failed!\n");
    free(a); free(b); exit(1);
  }

  // init input and output matrices
  for (int i=0;i<N*N;i++) {
    a[i] = rand()%10+1;#include <stdio.h>
#include <stdlib.h>
#include <emmintrin.h>
#include <sys/time.h>

// this is the float version of dot product of two NxN matrices 
// compile with: gcc -Wall -O2 mmult-float.c -o mmult-float -DN=1000

// NOTE: in order to be cache friendly, matrix B is assumed to be transposed
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <emmintrin.h>


// this is the float version of dot product of two NxN matrices 
// compile with: gcc#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <emmintrin.h>


// this is the float version of dot product of two NxN matrices 
// compile with: gcc#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <emmintrin.h>


// this is the float version of dot product of two NxN matrices 
// compile with: gcc#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <emmintrin.h>


// this is the float version of dot product of two NxN matrices 
// compile with: gcc -Wall -O2 mmult-float.c -o mmult-float -DN=1000

// NOTE: in order to be cache friendly, matrix B is assumed to be transposed


void get_wallti -Wall -O2 mmult-float.c -o mmult-float -DN=1000

// NOTE: in order to be cache friendly, matrix B is assumed to be transposed


void get_wallti -Wall -O2 mmult-float.c -o mmult-float -DN=1000

// NOTE: in order to be cache friendly, matrix B is assumed to be transposed


void get_wallti -Wall -O2 mmult-float.c -o mmult-float -DN=1000

// NOTE: in order to be cache friendly, matrix B is assumed to be transposed


void get_wallti

void get_walltime(double *wct) {
  struct timeval tp;
  gettimeofday(&tp,NULL);
  *wct = (double)(tp.tv_sec+tp.tv_usec/1000000.0);
}


int main() {
double ts,te;
float *a,*b,*c;
__m128 *pa,*pb;
int i;
  // allocate test arrays - request alignment at 16 bytes
  i = posix_memalign((void **)&a,16,N*N*sizeof(float));
  if (i!=0) exit(1);
  i = posix_memalign((void **)&b,16,N*N*sizeof(float));
  if (i!=0) { free(a); exit(1); }
  // i = posix_memalign((void **)&c,16,N*N*sizeof(float));
  // if (i!=0) { free(b); free(a); exit(1); }
  
  // //initialize float input test arrays fa, fb
  // pa[0] = 1.0; pa[1] = 2.0; pa[2] = 3.0; pa[3] = 4.0;
  // pb[0] = 1.1; pb[1] = 2.2; pb[2] = 3.3; pb[3] = 4.4;

  // alias the sse pointers to input and output test arrays
  pa = (__m128 *)a; 
  pb = (__m128 *)b;
  // vfc = (__m128 *)pc;

  // a = (float *)malloc(N*N*sizeof(float));
  // if (a==NULL) {
  //   printf("Allocation failed!\n");
  //   exit(1);
  // }
  
  // b = (float *)malloc(N*N*sizeof(float));
  // if (b==NULL) {
  //   printf("Allocation failed!\n");
  //   free(a); exit(1);
  // }

  c = (float *)malloc(N*N*sizeof(float));
  if (c==NULL) {
    printf("Allocation failed!\n");
    free(a); free(b); exit(1);
  }

  // init input and output matrices
  for (int i=0;i<N*N;i++) {
    a[i] = rand()%10+1;
    b[i] = rand()%10+1;
    c[i] = 0.0;
  }

  // get starting time (double, seconds) 
  get_walltime(&ts);

  // // horizontal sum of the 4 packed floats
  

  // load, matrix multiplication
  for (int i=0;i<N;i++) {	// for all rows of A,C
  
    for (int j=0;j<N;j++) {	// for all "columns" (rows) of B
    
      __m128 sum;
      sum=_mm_setzero_ps();
      for (int k=0;k<N/4;k++) {	// for each element of selected A row and B "column"
        sum += _mm_add_ps(sum,_mm_mul_ps(pa[i*N/4+k],pb[j*N/4+k]));	// a[i,k]*b[j,k]  NOTE: B is transposed, originally b[k,j]
      }
      __m128 t1 = _mm_shuffle_ps(*pa,*pa,_MM_SHUFFLE(2,3,0,1)); // C D A B
      __m128 t2 = _mm_add_ps(*pa,t1);			    // D+C C+D B+A A+B
      t1 = _mm_movehl_ps(t1,t2);				    // C D D+C C+D
      t2 = _mm_add_ss(t1,t2);				    // C D D+C A+B+C+D
      // fsum = _mm_cvtss_f32(t2); 
      c[i*N+j]=_mm_cvtss_f32(t2);	// c[i,j]
    
    }
  
  }

  // get ending time
  get_walltime(&te);

  // print computation time
  printf("Computation time = %f sec\n",(te-ts));

  // test result (i.e. check that all elements of c were "touched"
  for (int i=0;i<N*N;i++) {
    if (c[i]==0.0) { printf("Error!\n"); break; }
  }


  free(c);
  free(b);
  free(a);
  
  return 0;
}

    b[i] = rand()%10+1;
    c[i] = 0.0;
  }

  // get starting time (double, seconds) 
  get_walltime(&ts);

  // // horizontal sum of the 4 packed floats
  

  // load, matrix multiplication
  for (int i=0;i<N;i++) {	// for all rows of A,C
  
    for (int j=0;j<N;j++) {	// for all "columns" (rows) of B
    
      __m128 sum;
      sum=_mm_setzero_ps();
      for (int k=0;k<N/4;k++) {	// for each element of selected A row and B "column"
        sum += _mm_add_ps(sum,_mm_mul_ps(pa[i*N/4+k],pb[j*N/4+k]));	// a[i,k]*b[j,k]  NOTE: B is transposed, originally b[k,j]
      }
      __m128 t1 = _mm_shuffle_ps(*pa,*pa,_MM_SHUFFLE(2,3,0,1)); // C D A B
      __m128 t2 = _mm_add_ps(*pa,t1);			    // D+C C+D B+A A+B
      t1 = _mm_movehl_ps(t1,t2);				    // C D D+C C+D
      t2 = _mm_add_ss(t1,t2);				    // C D D+C A+B+C+D
      // fsum = _mm_cvtss_f32(t2); 
      c[i*N+j]=_mm_cvtss_f32(t2);	// c[i,j]
    
    }
  
  }

  // get ending time
  get_walltime(&te);

  // print computation time
  printf("Computation time = %f sec\n",(te-ts));

  // test result (i.e. check that all elements of c were "touched"
  for (int i=0;i<N*N;i++) {
    if (c[i]==0.0) { printf("Error!\n"); break; }
  }


  free(c);
  free(b);
  free(a);
  
  return 0;
}
