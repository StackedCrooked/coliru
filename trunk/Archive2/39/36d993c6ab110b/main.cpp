#include <string>

template<typename T>
std::string to_string(const T& val)
{
    std::ostringstream stream; 
    stream  << val;
    return stream.str();
}


int main(){  }

