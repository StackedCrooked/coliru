#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

class Initializer {
private:
    static int i;
public:
    int operator() ()
    {
        return i++;
    }
};


// static members need definition
int Initializer::i;

int main()
{
    vector<int> v(10);
    generate(v.begin(), v.end(), Initializer());
    copy(v.begin(), v.end(), ostream_iterator<int>(std::cout, " "));
}