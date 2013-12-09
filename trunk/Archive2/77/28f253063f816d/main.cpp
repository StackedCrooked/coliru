#include <iostream>
#include <string>
#include <vector>

void sortfun(std::string listBooks[], int numofBooks)
{
    std::cout << "List of books in alphabetical order" << std::endl;
    
    for (int i = 0; i < numofBooks; ++i)
    {
        for (int k = 0; k < numofBooks; ++k)
        {
            if (listBooks[i] < listBooks[k])
            {
                std::string temp = listBooks[i];
                listBooks[i] = listBooks[k];
                listBooks[k] = temp;
            }
        }
    }
    
    for (int i = 0; i < numofBooks; ++i)
    {
        std::cout << listBooks[i] << std::endl;
    }
}

int main()
{
    std::string v[6] = {"a", "x", "c", "y", "w", "x"};
    sortfun(v, 6);
}