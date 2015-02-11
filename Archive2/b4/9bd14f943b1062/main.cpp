#include <stdio.h>    
#define SIZE 5
int G_funcs_called;   /* Global for number of function calls made */
/* Function Prototypes */
float average(float array[], int size);
void array_times_position(float array[], int size);

int main(void)
{
   float array[SIZE] = { 10.0, 20.0, 30.0, 40.0, 50.0 };
   printf("The average of the original array is %.2f\n",
          average(array, SIZE));
   array_times_position(array, SIZE);
   printf("The average of the new array is %.2f\n",
           average(array, SIZE) );
   array_times_position(array, SIZE);
   printf("The average of the new array is %.2f\n",
           average(array, SIZE) );
   printf("%d function calls have been made.\n", G_funcs_called);
}
