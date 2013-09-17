#include <iostream>
#include <string>

template<typename DocIdType,typename DocType>
struct Document {};

template<typename DocIdType>
std::ostream & operator << (std::ostream & os, const Document<DocIdType,std::string> & doc) {
   return os << "for string";
}

template<typename DocIdType,typename DocType>
std::ostream & operator << (std::ostream & os, const Document<DocIdType,DocType> & doc) {
   return os << "for generic";
}

using namespace std;

int main(int argc, char *argv[])
{
    std::cout << Document<struct anything, std::string>() << "\n";
    std::cout << Document<struct anything, struct anything_else>() << "\n";
}
