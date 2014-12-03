#include <iostream>

int main(){
    
	int f[10];
	int values[2] = {0,1};
	int *pos;
	int x = 9;
    
    std::cout << f << std::endl;
    std::cout << &f[0] << std::endl;
    std::cout << &f[9] << std::endl;
    std::cout << f + x << std::endl;
   
    while (x >= 0){
    	pos = f + x;
    	*pos = *(values+x%2);
        --x;
    }

for(auto a : f)
    std::cout << a << std::endl;
}