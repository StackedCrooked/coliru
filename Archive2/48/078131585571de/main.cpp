#include <vector>
#include <algorithm>
using namespace std;

struct user
{
    vector<size_t> follower;
    vector<size_t> following;
};

int main ()
{
    vector< user > node ( 100 );

    // Pushing back some indices of other nodes in some node[x].follower and node[x].following

    size_t i = 2;

    for ( size_t const& j : node[i].follower )
        node[j].following.erase( remove( node[j].following.begin(), node[j].following.end(), i ), node[j].following.end() );

}
