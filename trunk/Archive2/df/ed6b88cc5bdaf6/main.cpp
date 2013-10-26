#include <string>
#include <array>
#include "boost/lexical_cast.hpp"

using namespace std;
using boost::lexical_cast;
using boost::bad_lexical_cast;

int main() {
    int s=23;

    string str = lexical_cast<string>(s);
    str = "Message: " + lexical_cast<string>('A') + "=" + lexical_cast<string>(34.5);
    cout << str << endl;

    array<char, 64> msg = lexical_cast< array<char, 64> >(23);

    for(auto& s: msg)
        std::cout << s << ' ';
        
    s=lexical_cast<int>("3456");

    try {
       s = lexical_cast<int>("56.78");  // bad_lexical_cast
    } catch(bad_lexical_cast & e) {
       cout << "Exception caught: " << e.what() << endl;
    }

   return 0;
}
