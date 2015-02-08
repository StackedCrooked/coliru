#include <stdio.h>    
extern int G_funcs_called;

void array_times_position( float array[], int size)
{
   int i;
   for (i=0; i<size; i++)
        array[i] *= i;
   G_funcs_called++;
}

float average(float array[], int size)
{
   static int average_func_called;
   int i;
   float sum=0.0;

      average_func_called++; 
      G_funcs_called++;
      for( i=0; i<size; i++)
           sum += array[i];

      printf("average has been called %d time(s)\n",  
              average_func_called);
      return sum/size; /* Calculate and return the average */
}

