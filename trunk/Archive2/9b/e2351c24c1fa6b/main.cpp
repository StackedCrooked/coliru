#include <iostream> 
#include <cstdlib> 

using namespace std; 

struct ABC
{ 
    int n; 
    char c; 
    double a[3]; 
}; 


void get( int & n, char & c, double a[3], const ABC & x )
{ 
    n = x.n; 
    c = x.c; 

    for (int i = 0; i < 3; i++){ 
    a[i] = x.a[i]; 

    } 
} 

void get( int n[], char c[], double a[][3], const ABC x[], int elements )
{
    for (int i = 0; i < elements; i++){ 

    get(n[i], c[i], a[i], x[i]); 

    } 

} 

int main()
{ 

    int number = 42;
    char m = '?';
    ABC x = {number, m, {1, 2, 3}}; 

    ABC xx[4] = { 

    {123, 'A', {1.1, 1.2, 1.3}}, 
    {234, 'B', {2.1, 2.2, 2.3}}, 
    {345, 'C', {3.1, 3.2, 3.3}}, 
    {456, 'D', {4.1, 4.2, 4.3}} 

    }; 

    int n; 
    char c; 
    int a[4] = {}; 

    int n1 [4] = {}; 
    char c1 [4] = {}; 
    double a3 [4] [3] = {}; 

    int elements = 3; 

    get(n1, c1, a3, xx, elements); 

    return 0; 
} 
#include <iostream>
#include <vector>
#include <string>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

namespace qi = boost::spirit::qi;


struct VectorWrapper
{
    std::vector<std::string> data;
};

BOOST_FUSION_ADAPT_STRUCT(
    VectorWrapper,
    (std::vector<std::string>, data)
)

int main ()
{
    std::string input("aa aa aa");
    std::string::iterator strbegin = input.begin();

    qi::rule<std::string::iterator, VectorWrapper(), qi::space_type > testRule = 
        qi::eps >> +(qi::string("aa"));

    VectorWrapper result;
    bool ok = qi::phrase_parse(
            strbegin, 
            input.end(),
            testRule,
            qi::space,                  
            result);                               

    if (ok && strbegin == input.end()) {
        std::cout << result.data.size();
        for (size_t i = 0; i < result.data.size(); ++i) {
            std::cout << result.data[i] << " ";
        }
    } else {
        std::cout << "fail" << std::endl;
        std::cout << std::string(strbegin, input.end()) << std::endl;
    }
}
