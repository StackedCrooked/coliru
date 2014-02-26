#include <iostream> 
#include <cstdlib> 

using namespace std; 

struct ABC
{ 
    int n; 
    char c; 
    double a[3]; 
}; 


void get( int & n, char & c, double a[3], const ABC & x )
{ 
    n = x.n; 
    c = x.c; 

    for (int i = 0; i < 3; i++){ 
    a[i] = x.a[i]; 

    } 
} 

void get( int n[], char c[], double a[][3], const ABC x[], int elements )
{
    for (int i = 0; i < elements; i++){ 

    get(n[i], c[i], a[i], x[i]); 

    } 

} 

int main()
{ 

    int number = 42;
    char m = '?';
    ABC x = {number, m, {1, 2, 3}}; 

    ABC xx[4] = { 

    {123, 'A', {1.1, 1.2, 1.3}}, 
    {234, 'B', {2.1, 2.2, 2.3}}, 
    {345, 'C', {3.1, 3.2, 3.3}}, 
    {456, 'D', {4.1, 4.2, 4.3}} 

    }; 

    int n; 
    char c; 
    int a[4] = {}; 

    int n1 [4] = {}; 
    char c1 [4] = {}; 
    double a3 [4] [3] = {}; 

    int elements = 3; 

    get(n1, c1, a3, xx, elements); 

    return 0; 
} 
