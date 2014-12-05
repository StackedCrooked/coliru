#include <iostream>

int main (){
    
	int f[10] = {0, -1, -2, -3, -4, -5, -6, -7, -8, -9};
	int *pos;
	int x = 0;
    
    std::cout << &x << std::endl;
    
	while (x <10){
		pos = f + x;
		x+=2;
	}
            
    for(auto a: f) std::cout << a << std::endl;
}