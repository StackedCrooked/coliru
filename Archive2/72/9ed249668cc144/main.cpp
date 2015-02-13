
#include <iostream>

#include <tuple>
#include <type_traits>
#include <utility>

using namespace std;

struct cop 
{
    cop(){cout << "constr" << endl;}
    cop(const cop&){cout << "copy" << endl;}    
    cop(cop&&){cout << "move" << endl;}   
    cop & operator= (const cop &) {cout << "assign" << endl;
    cop & operator= (cop &&) {cout << "assign move" << endl;

    return *this;} 
};

pair<cop, cop> func() {
    cop c1;
    cop c2;
    return make_pair(std::move(c1), std::move(c2)); 
}



int main(int argc, char* argv[])
{
    
    cop c1, c2;
    tie(c1, c2) = func();

    return 0;
}
