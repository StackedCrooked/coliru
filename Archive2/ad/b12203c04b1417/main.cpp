#include <iostream>
 
int main()
{
    for(int i=0 ; i<5 ; i++) {
        for(int j=0 ; j<5 ; j++) {
            std::cout << j;
            if(i==2 && j==2) {
                std::cout << "<22>";
                break;
            }
        }
    }
}