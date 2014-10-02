#include <iostream>
#include <string>
#include <vector>
#include<omp.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#define size 10
using namespace std;




/* here, do your time-consuming job */



int main()
{int id;
clock_t begin, end;

double time_spent;
     
     double a[size][size],b[size][size],c[size][size];
     int i,j;
     for(i=0;i<size;i++)
     for(j=0;j<size;j++)
     a[i][j]=rand()%10;
     
     for(i=0;i<size;i++)
     for(j=0;j<size;j++)
     b[i][j]=rand()%10;
     
begin = clock();  

     for(i=0;i<size;i++)
     for(j=0;j<size;j++)
     c[i][j]=a[i][j]+b[i][j];
      end = clock();
time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("time_spent=%f\n",time_spent );
printf("%d\n",omp_get_max_threads());

printf("proc=%d\n",omp_get_num_procs());
omp_set_num_threads(42);
begin = clock();
  #pragma omp parallel //for
  {
    /* id=omp_get_thread_num(); 
  if(id==0)
 // cout << "num of threads"<< omp_get_num_threads() <<endl;
  printf("num of threads=%d\n",omp_get_num_threads() );*/
  for(i=0;i<size;i++)
     for(j=0;j<size;j++)
    { c[i][j]=a[i][j]+b[i][j];
    printf("by thread %d\n",omp_get_thread_num());
    }
      end = clock();
  }
    
    end = clock();
time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("time_spent in parallel=%f\n",time_spent );
   
    return 0;
}
