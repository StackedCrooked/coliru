#include <cstdlib>
#include <iostream>
#include <fstream> 
using namespace std;

int tour_cost (int start, int end, int* array, int* tour) //calculate tour cost
{
    int cost = 0;
    for (int i = start; i < end; i++) 
        cost += array[tour[i] * tour[i] + tour[i + 1]];
    return cost;
}

int main()   
{
    int array [625];
    int tour [25];
    int dist = 0;   
    ifstream infile ("cities.txt");
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 25; j++ ) {
            infile >> dist;
            array[i*i + j] = dist;
        }
        tour[i] = i;
    }
    cout << tour_cost (0,24,array,tour);
    return 0;
}