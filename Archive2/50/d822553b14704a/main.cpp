#include <map>
#include <set>
using namespace std;

class A {

    struct cmpr_t {
        bool operator() (int k1, int k2) {
            return mp[k1] < mp[k2];  // doesn't compile
        }
    };

    static map<int, int> mp;  // storing key->value
    static set<int, cmpr_t> ss;  // just keys, ordered by corresponding value in mp
};

int
main()
{
}