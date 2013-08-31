#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <boost/range/adaptor/reversed.hpp>


using namespace std;


int main()
{
    string s { "OMG LOL!" };
    cout << (s | boost::adaptors::reversed);

}