#include <map>
using namespace std;

class C {
public:
    C(map<int,int> m) { }
    int operator()(int a, int b) {
        return a < b;
    }
};
    
int main() {
    
    map<int, int> m;
    map<int, int, C> mymap(C(m));
    mymap.insert(pair<int,int>(1,1));
}
    