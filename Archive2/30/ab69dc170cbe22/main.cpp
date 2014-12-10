#include <iostream>
#include <stdlib.h>  //atoi

int main(int argc, char *argv[]) {
    if(argc != 2) {
		std::cout << "Invalid argument. Usage: " << argv[0] << " <array size>" << std::endl;
        std::cout << "Array size should be 2^n" << std::endl;
        return -1;
	}

	int arrsize = atoi(argv[1]);
    if((arrsize & (arrsize - 1)) != 0) {
        std::cout << "Array size is not 2^n" << std::endl;
        return -1;
    }
    
	int my_array[arrsize];

	for(int i = 0; i < arrsize; ++i)
		my_array[i] = i;

	//sequential, unoptimized sum reduction
	for(int i = arrsize/2; i > 0; i = i/2) {
		for(int j = 0; j < i; ++j) {
            my_array[j*(arrsize/i)] += my_array[j*(arrsize/i) + (arrsize/i)/2];
        }
	}

    std::cout << my_array[0] << std::endl;
    
    int sum=0;
    for(int i = 0; i < arrsize; ++i)
        sum+=i;
    std::cout << sum << std::endl;
} 