#include <iostream>

int main()
{
    int s=0;
    for(int i=0;i<1000000000;i++){
		s+=__builtin_popcountll(i);
	}
    std::cout<<s;
}
