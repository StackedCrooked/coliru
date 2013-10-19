#include <vector>
#include <algorithm>
int main()
{
    int a;
    std::vector< std::vector <int> > v;
    std::vector< std::vector <int> >::const_iterator it = std::find( v.begin(), v.end(), a );
}