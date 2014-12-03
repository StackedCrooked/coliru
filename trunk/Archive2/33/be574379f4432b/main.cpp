#include <iostream>

int main (){
    
	int f[10] = {0, -1, -2, -3, -4, -5, -6, -7, -8, -9};
	int values[2] = {7,3};
	int *pos;
	int x = 0;
	while (x <10){
		pos = f + x;
		x+=2;
		*pos = (int)(&x);
	
			}
            
    for(auto a: f) std::cout << a << std::endl;
}