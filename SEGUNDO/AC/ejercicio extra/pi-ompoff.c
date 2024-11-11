/**
 * 
PI secuencial con integración numérica. 
 * 
 */
#include <stdlib.h>
#include <stdio.h>
//#define _USE_MATH_DEFINES
#include <math.h>
#ifdef _OPENMP
#include <omp.h>
#else
	#define omp_get_max_threads() 1
#endif
//#include <time.h>
/**
 * @file  pi.c 
 * @brief PI secuencial con integración numérica, área de rectángulos
 * @author Mancia Anguita
 *  
 * **Compilación**
 * @code
 *  gcc -O2 pi.c -o pi
 * @endcode
 * 
 *  **Ejecución**
 * ~~~~~~~~~~~~~~~~~~~~~
 * ./pi   1000000    (1000000 intervalos de integración)
 * ~~~~~~~~~~~~~~~~~~~~~
 * 
*/
int main(int argc, char **argv)
{
  register double width;
  double sum;
  register int intervals, i; 
  //struct timespec cgt1,cgt2; double ncgt; 
  double t0 = 0, t1=0, t2=0, t3=0; //para tiempo
    
  //Los procesos calculan PI en paralelo
  if (argc<2) {printf("Falta número de intevalos");exit(-1);}
  intervals=atoi(argv[1]);  
  if (intervals<1) {intervals=1E6; printf("Intervalos=%d",intervals);}
  
  width = 1.0 / intervals;
  sum = 0;
  register double x;
  // clock_gettime(CLOCK_REALTIME,&cgt1);
  t0 = omp_get_wtime();
  
  #pragma omp target enter data map(to: sum, intervals, width, x)
  
  t1=omp_get_wtime();
  
  #pragma omp target teams distribute parallel for reduction(+:sum)
	  for (i=0; i<intervals; i++) {
	    x = (i + 0.5) * width;
	    sum += 4.0 / (1.0 + x * x);
	  }
  

  
  t2=omp_get_wtime();
  
  #pragma omp target exit data map (delete: intervals, width, x) map(from:sum)
  
  sum *= width;
    
  t3=omp_get_wtime();
  
  double suma_final = fabs(M_PI-sum);
  
  printf("Iteraciones:\t%d\t. PI:\t%26.24f\t. Tiempo:\t%8.6f\t. Tiempo de transferencia hacia GPU:\t%8.6f\t. Tiempo de transferencia desde GPU:\t%8.6f\t. Error:\t%8.6f\n", intervals,sum,t2-t1, t1-t0, t3-t2, suma_final);
  

  return(0);
}



