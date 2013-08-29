#include <iostream>
#include <thread>

struct s {
    int x ; 
} time1 ; 

int main()
{
    time1.x = 2 ; 
    std::cout << "\n\nOutput : " << time1.x ; 
    //time1 ob ; 
}