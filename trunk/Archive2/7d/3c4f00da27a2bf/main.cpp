#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>

using namespace std;
 
int main()
{
    // jbnjk rger
    random_device rd;   // non-deterministic generator
    mt19937 gen(rd());  // to seed mersenne twister.
    negative_binomial_distribution<int> dist(3,0.5); // 

    cout << "These are some numbers that are negatively binomially distributed about a mean of pr/(1-p): ";
    for (int i = 0; i < 20 ; ++i) {
        cout << dist(gen) << " "; // pass the generator to the distribution.
    }
    cout << endl;

	return 0;
	
}