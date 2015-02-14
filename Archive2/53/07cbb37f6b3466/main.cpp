#include <stdio.h>
#include <stdlib.h>
 
void printline(void);
void setlength(unsigned char **array, unsigned int *sizead, unsigned int size);
int main()
{
    unsigned char *myarray; //define the pointer that will hold the array
    unsigned int size = 0; //variable to keep track of the array's size, since impossible otherwise (from what i've read)
 
    printf("Size of array: %d",size); printline(); //prints the size variable before function, i also hate typing \n
    setlength(&myarray, &size, 3);
    printf("Size of array: %d",size); printline(); //prints the size variable after function
 
    getchar(); //crashes after this
 
    myarray[0] = 5;
    printf("If you see this, the array-write succeeded."); printline();
    printf("The value of array element 0: %d",myarray[0]);
 
    getchar(); //testing
    return 0;
}
 
void printline(void)
{
    printf("\n");
}
 
void setlength(unsigned char **array, unsigned int *sizead, unsigned int size)
/*
the function takes:
>>the address of the pointer/array to have memory allocated to
>>the address of the variable that keeps track of its size
>>the size desired, an integer
*/
{
    *sizead = size; //sets the size variable's value to size value
    *array = (unsigned char*)malloc (size * sizeof(**array)); //allocates memory to the array, for size number of elements
}