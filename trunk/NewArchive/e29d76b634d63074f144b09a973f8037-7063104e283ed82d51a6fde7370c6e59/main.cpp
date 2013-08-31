#include <iostream>
#include <string>
#include <vector>
using namespace std;


using Sentence = vector<string>;


ostream& operator<<(ostream& os, const Sentence & sentence)
{
    for (const auto & word : sentence)
    {
        os << word << " ";
    }
    return os;
}


int main()
{
    Sentence sentence = { "Hello", "from", "GCCC", __VERSION__, "!" };    
    cout << sentence << endl;
}
