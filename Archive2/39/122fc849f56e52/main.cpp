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
    int b[] = 1, 35, 14, 47, 10 };
    int c[] = 9, 19,  3, 42, 24 };
    int d[] = 33, 27, 23, 4, 28 };
    int e[] = 26, 33, 40, 8, 23 };
    int f[] = 46, 47, 43, 2, 32 };
    int g[] = 24, 16, 17, 33, 14 };
    int h[] = 10, 22, 12, 31, 18 };
    int i[] = 18, 2, 36, 27, 37 };
    int j[] = 47, 17, 37, 3, 23 };
    int k[] = 24, 28, 43, 46, 7 };
    int l[] = 2, 11, 13, 16, 22 };
    int m[] = 30, 06, 41, 7, 43 };
    int n[] = 17, 47, 32, 22, 9 };
    int o[] = 29, 01, 26, 3, 37 };
    int p[] = 29, 19, 18, 45, 27};
    std::map<int,int> m; 

    // load the map
    for(unsigned int i=0; i< sizeof(a)/sizeof(a[0]); i++) 
        m [a[i]]++;

    // find the max occurence...
    maxoccur ret = std::for_each(m.begin(), m.end(), maxoccur());
    std::cout << "value:" << ret._M_val << " max repetition:" << ret._M_rep <<  std::endl;

    return 0;
}