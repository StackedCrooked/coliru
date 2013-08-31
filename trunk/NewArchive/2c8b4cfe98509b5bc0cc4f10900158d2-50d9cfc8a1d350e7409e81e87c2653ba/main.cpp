#include <iostream>
#include <string>
#include <vector>
#include <boost/coroutine/coroutine.hpp>


int main()
{
    Sentence sentence = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << sentence << std::endl;
}
