#include <iostream>
 
int main(){
    int solution = 0;
    int length = 0; 
    int maxlength = 0;
    int j = 1, k;
 
    for(int n = 997; n > 1; n -= 2){
        j = 1;
        for(int i = 0; i < n; i++)
            j = (j*10) % n;
        k = j;
        length = 0;
        do{
            j = (j*10) % n;
            length++;
        } while(j != k);
        if(length > maxlength){
            solution = n;
            maxlength = length;
        }
    }
    std::cout << "Solution: " << solution << std::endl;
}