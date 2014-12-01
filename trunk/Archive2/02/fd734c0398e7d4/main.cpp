
#include <vector>
#include <climits>

typedef std::vector<int> ivec;

// return index of max element
int max_index( const ivec& v )
{
    if( v.empty() ) return -1;
    
    int idx = 0;
    int max = v[0];
    
    for(int i=1; i<v.size(); ++i)
    {
        if( v[i] > max )
        {
            max = v[i];
            idx = i;
        }
    }
    
    return idx;
}

// return indexes of N top elements
ivec top( const ivec& vec, int N )
{
    ivec tmp(vec);
    ivec res;
    for(int i=0; i<N; ++i )
    {
        int idx = max_index(tmp);
        res.push_back(idx);
        tmp[idx] = INT_MIN;
    }
    return res;
}

#include <iostream>

int main()
{
    ivec iv1 = { 55,66,77,88,2,4,5,6,99,123,22 };
    ivec iv2 = top( iv1, 5 );
    
    for( auto&& elem : iv2 )
    {
        std::cout << "idx:" << elem << " val:" << iv1[elem] << "\n";
    }
}

