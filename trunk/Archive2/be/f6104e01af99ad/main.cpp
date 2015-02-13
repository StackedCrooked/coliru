#include <string>
#include <iostream>
#include <boost/lexical_cast.hpp>
using namespace std;
using namespace boost;

 
int main(){
    cout << lexical_cast<int>("111!") << endl;
}
