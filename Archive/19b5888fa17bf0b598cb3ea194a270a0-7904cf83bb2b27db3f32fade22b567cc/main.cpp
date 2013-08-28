#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
using namespace std;

mutex mt;

struct ThreadPrimary1 {
    ThreadPrimary1(const int numRecords) : maxCount(numRecords) {
        for (int counter = 0; counter < maxCount; counter++) {
            if (counter % 2 == 0) {
                vPrimary1.push_back(counter);
            }
        }
    }
    
    void operator () () {
        int size = vPrimary1.size();
        
        if (mt.try_lock()) {
            for (int counter = 0; counter < size; counter++) {
                cout<<endl<<vPrimary1[counter];
            }
            mt.unlock();
        }
    }
private:
    vector<int> vPrimary1;
    int maxCount;
};

struct ThreadPrimary2 {
    ThreadPrimary2(const int numRecords) : maxCount(numRecords) {
        for (int counter = 0; counter < maxCount; counter++) {
            if (counter % 2 == 1) {
                vPrimary2.push_back(counter);
            }
        }
    }
    
    void operator () () {
        int size = vPrimary2.size();
        
        if (mt.try_lock()) {
            cout<<endl<<"Inside the ThreadPrimary2 function thread";
            for (int counter = 0; counter < size; counter++) {
                cout<<endl<<vPrimary2[counter];
            }
            mt.unlock();
        }
    }
private:
    vector<int> vPrimary2;
    int maxCount;
};

int main()
{
    thread t1{ThreadPrimary1(10)};
    thread t2{ThreadPrimary2(20)};
    
    t1.join();
    t2.join();
    return 1;
}
