#include <stdio.h>

void minmaxrec(int* array, int length, int& min, int& max)
{
    if(!length)
        return;
        
    if(array[length - 1] > max)
        max = array[length - 1];
    if(array[length - 1] < min)
        min = array[length - 1];
        
    minmaxrec(array, length - 1, min, max);
}

int main(int argc, char **argv) {
	int array[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int min = 100, max = 0;
    
    minmaxrec(array, 10, min, max);
    
    printf("min: %d, max: %d", min, max);

	return 0;
}