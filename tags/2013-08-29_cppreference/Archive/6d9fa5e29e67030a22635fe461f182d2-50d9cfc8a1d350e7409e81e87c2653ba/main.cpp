
void insertionSort (int arrtosort[], int size)
{
 int temp = arrtosort[0];
 for(int i = 1; i < size; i++)
{
    temp = arrtosort[i];
    int j = 0;
    for(j = i; j > 0; j--)
        if(temp < arrtosort[j - 1])
           arrtosort[j] = arrtosort[j - 1];
        else break;
    arrtosort[j-1] =  temp;
}
}

#include <algorithm>
#include <iostream>

int main() {
    {
        int data[15][3] = {
            {0, 0, 1},
            {0, 1, 0},
            {1, 0, 0},
            {0, 1, 1},
            {1, 0, 1},
            {1, 1, 0},
            {0, 1, 2},
            {0, 2, 1},
            {1, 0, 2},
            {1, 2, 0},
            {2, 0, 1},
            {2, 1, 0},
        };
        for(int i=0; i<8; ++i)  {
            insertionSort(data[i], 3);
            if (std::is_sorted(data[i], data[i]+3) == false)
                std::cerr << "set " << i << "incorrectly sorted as " << data[i][0] << ',' << data[i][1] << ',' << data[i][2] << '\n';
        }
    }
    {
        int data[3][2] = {
            {0, 0},
            {0, 1},
            {1, 0},
        };
        for(int i=0; i<3; ++i)  {
            insertionSort(data[i], 2);
            if (std::is_sorted(data[i], data[i]+2) == false)
                std::cerr << "set " << i << "incorrectly sorted as " << data[i][0] << ',' << data[i][1] << '\n';
        }
    }
    {
        int data = 0;
        insertionSort(&data, 1);
        //just don't crash
    }
    std::cout << "pass";
    return 0;
}