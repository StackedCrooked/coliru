#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

struct Time {
    int h;
    int m;
    int s;
};

class CompareTime {
public:
    bool operator() (Time& t1, Time& t2) {
        if (t1.h < t2.h) return true;
        if (t1.h == t2.h && t1.m < t2.m) return true;
        if (t1.h == t2.h && t1.m == t2.m && t1.s < t2.s) return true;
        return false;
    }
};

int main() {
    priority_queue<Time, vector<Time>, CompareTime> pq;
    pq.push({3,2,40});
    //pq.emplace(3,2,26);
    //pq.emplace(5,16,13);
    //pq.emplace(5,14,20);

    while(!pq.empty()) {
        Time t2 = pq.top();
        cout << setw(4) << t2.h << " " << setw(3) << t2.m << " " << setw(3) <<
            t2.s << endl;
        pq.pop();
    }
    return 0;

}