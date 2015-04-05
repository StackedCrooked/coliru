#include <iostream>
#include <chrono>
#include <random>
#include <ctime>
#include <algorithm>

using std::swap;

void bubbleSort(int arr[], int size)
{
    for(int i =0; i< size - 1; i++)
    {
        int minimum = arr[i];
        for(int j = i+1; j < size; j++)
        {
            if(minimum > arr[j])
            {
                minimum = arr[j];
                swap(arr[i], arr[j]);
            }
        }
    }
}

void selectionSort(int arr[], int size)
{
    int min;
    for(int i =0; i< size; i++)
    {
        min = i;
        for(int j = i; j < size; j++)
        {
            if(arr[j] < arr[min])
            {
                min = j;
            }
        }
            swap(arr[i], arr[min]);
    }
}

int main()
{
    const int SIZE = 1000;
    std::mt19937 gen;
    gen.seed(time(NULL));
    std::uniform_int_distribution<> dis(0, 99);
    
    for (int set = 1; set <= 10; ++set)
    {
        std::cout << "Set " << set << std::endl;
        int a[SIZE], b[SIZE];
        for (int i = 0; i < SIZE; ++i)
            a[i] = b[i] = dis(gen);
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        selectionSort(a, SIZE);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "\tSelection sort took "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
                  << " microseconds.\n";
        start = std::chrono::steady_clock::now();
        bubbleSort(b, SIZE);
        end = std::chrono::steady_clock::now();
        std::cout << "\tBubble sort took "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
                  << " microseconds.\n";
    }
    
    return 0;
}