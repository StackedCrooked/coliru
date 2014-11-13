#include <vector>
#include <algorithm>

namespace Namespace
{
    struct Bar
    {
    };

    bool barComparator(Bar& bar1 , const Bar& bar2 )
    {
        return true;
    }

    struct Foo
    {   
        void doStuff()
        {
            std::vector<Bar> barVec;
            std::sort( barVec.begin() , barVec.end() , barComparator );
        }
    };
}   

int main()
{
}