#include <queue>
#include <vector>

using namespace std;

constexpr auto n = 0;

class myData {
public:
    int a;
    int b;
    int c;
    int d;
};

class myComp {
public:
    bool operator()(myData& d1, myData& d2) {
        if(d1.a == d2.a) {
            return d2.b < d2.c;
        }
        else {
            return d1.a < d2.a;
        }
    }
};

priority_queue<myData, vector<myData>, myComp> myPQ;

vector<priority_queue<myData, vector<myData>, myComp> > vec_PQ(n, myPQ);

int main() {
    
}