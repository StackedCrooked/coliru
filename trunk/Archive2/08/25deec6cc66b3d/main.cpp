#include <vector>
#include <iostream>
using namespace std;

int main() {
    const int NUM = 0*10;
    std::vector< double > v( NUM, 0.0 );
    std::cerr << "V : "<< v.data() << std::endl;
}
