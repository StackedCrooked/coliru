//ciao Franz :-)
#include <iostream>
#include <string>
int main(){for( int i = 0; i < 21; ++i ) std::cout << std::string(abs(10-i),'-') << std::string(21-2*abs(10-i),'*') << std::string(abs(10-i),'-') << std::endl;}