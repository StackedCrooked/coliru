#include <bitset>
#include <cmath>
#include <iostream>
#include <numeric>

void showBits(int num){
    std::bitset<32> bits(num);
	std::cout << bits<<'\n';
}

int main(int argc, char** argv) {
  
	showBits(2);
	showBits(-2);
    std::cout<<"agar deghat konid -2 az baraks kardan bit haye 2 va jam zadan ba 1 bedast miad\n";

    std::cout<< (int)std::pow(2,31)<<'\n';
    std::cout<< std::numeric_limits<int>::max()<<'\n';
}
