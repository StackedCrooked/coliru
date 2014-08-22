#include <vector>
#include <iostream>
#include <tuple>
#include <stdlib.h> 
#include <array>

using namespace std;

int main(){
    
    using T  = tuple<int, float, char>;
    using el = tuple_element_t<0, T>;
}
