/* @name noko<3Alastor
 * @author nokosage
 * @date 2/15/2014
 * @purpose to show Alastor my way of doing what he did
 */
#include <iostream>                                                 //cout, endl()
#include <vector>                                                   //vector<>
using namespace std;                                                //std::

int main()
{
    vector<int> v1{1, 2, 3, 4, 5},
                v2{5, 4, 3, 2, 1, 0, 1, 2, 3, 4};
    size_t greatest_size{v1.size()};                                //Initialize greatest_size to actual data
    
    if (v1.size() > v2.size())                                      ///If: the size of v1 is greater than v2,
    {
        greatest_size = v1.size();
        //for (int i = 0; i < int(v1.size() - v2.size()); i++)      //Old for loop method (the one I showed you).
        //    v2.push_back(0);
        v2.resize(v1.size(), 0);                                    //Use the resize method on v2 to match the size of v1 (defaulting to 0 values).
    }
    else if (v2.size() > v1.size())                                 ///Else if: the size of v2 is greater than v1,
    {
        greatest_size = v2.size();
        //for (int i = 0; i < int(v2.size() - v1.size()); i++)      //Old for loop method (the one I showed you) again.
        //    v1.push_back(0);
        v1.resize(v2.size(), 0);                                    //Use the resize method on v1 to match the size of v2 (defaulting to 0 values).
    }                                                               ///Else: they are the same, do nothing
    
    vector<int> datsumdoe(greatest_size);                           //We will use greatest_size here for the sake of clarity
    for(size_t idy = 0; idy < greatest_size; ++idy)
    {
        cout << v1[idy] << ' ';
    }
    
    cout << endl;
    for(size_t idy = 0; idy < greatest_size; ++idy)
    {
        cout << "+ ";
    }
        
    cout << endl;
    for(size_t idy = 0; idy < greatest_size; ++idy)
    {
        cout << v2[idy] << ' ';
    }
    
    cout << endl;
    for(size_t idy = 0; idy < greatest_size; ++idy)
    {
        cout << "= ";
    }
    
    cout << endl;
    for(size_t idy = 0; idy < greatest_size; ++idy)
    {
        datsumdoe[idy] = v1[idy] + v2[idy];
        cout << datsumdoe[idy] << ' ';
    }
}