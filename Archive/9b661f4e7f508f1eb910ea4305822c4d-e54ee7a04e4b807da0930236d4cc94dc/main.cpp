#include <iostream>

int global_i = 42;

int function (int j)
{
    global_i = 84;
    return j=j*5;
}
        
int main ()
{
    int i=0;
    int array[11] = {};
       
    for(; i < 11; ++i)
    {
        array[i] = i + 6;
    }

    for (i=0; i < 11; ++i)
    {
        std::cout << array[i] << " ";
    }
    std::cout<<"\nglobal_i: " << global_i << "\n";
    
    for (i=0 ; i <11; i++)
    {
        std::cout<<function (array [i]) <<" ";
    }
    
    std::cout << "\nglobal_i: " << global_i;
}



