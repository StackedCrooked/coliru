#include <iostream>
#include <algorithm>
#include <map>

// functor
struct maxoccur
{
    int _M_val;
    int _M_rep;

    maxoccur()
    : _M_val(0),
      _M_rep(0)
    {}

    void operator()(const std::pair<int,int> &e)
    {
        std::cout << "pair: " << e.first << " " << e.second << std::endl;
        if ( _M_rep < e.second ) {
            _M_val = e.first;
            _M_rep = e.second;
        }
    }
};

int
main(int argc, char *argv[])
{
    int a[] = {16, 21, 37, 26, 17 };    
    std::map<int,int> x; 

    // load the map
    for(unsigned int i=0; i< sizeof(a)/sizeof(a[0]); i++) 
        x[a[i]]++;

    // find the max occurence...
    maxoccur ret = std::for_each(x.begin(), x.end(), maxoccur());
    std::cout << "value:" << ret._M_val << " max repetition:" << ret._M_rep <<  std::endl;

    return 0;
}