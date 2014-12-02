#include <iostream>
#include <vector>

int main()
{
    std::vector< std::vector<int> > v ; // this is an empty vector
    v.resize(2) ; // now it contains two elements; v[0] and v[1]

    v[0].push_back(0);
    v[0].push_back(1);
    v[0].push_back(2);
    v[0].push_back(3);

    v[1].push_back(10);
    v[1].push_back(11);
    v[1].push_back(12);
    v[1].push_back(13);

    std::size_t i = 0, j = 4 ;

    // is v[i][j] present?
    if( i < v.size() && j < v[i].size() ) // i, j are valid
    {
        std::cout << "v[" << i << "][" << j << "] == " << v[i][j] << '\n' ;
    }
    else
    {
        std::cout << "there is no v[" << i << "][" << j << "]\n" ;
    }
}
