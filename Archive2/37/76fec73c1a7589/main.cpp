#include <iostream>

void leSort(int *a, int size)
{
    int temp = 0;
    for(int i = 0; i < size; i++)
    {
		for (int j = 0; j < size-1; j++)
        {
            if (a[j] > a[j+1])
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
        }
	}
}

int main()
{
    int array[] = {321, 213, 44, 9, 23, 76, 73, 22};
    leSort(array, 8);
    
    //Print le contents of le array
    for(int i = 0; i < 8; i++)
    {
        std::cout << i << ". " << array[i] << std::endl;   
    }
    return 0;
}
