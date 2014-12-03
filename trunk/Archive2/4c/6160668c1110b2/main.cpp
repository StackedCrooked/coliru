#include <condition_variable>
#include <mutex>
#include <future>
#include <iostream>
#include <chrono>
#include <queue>
#include <thread>

using namespace std;

int count = 10;
condition_variable cv;
mutex mu;
queue<int> q;

void producer(int id) {
   cout << "producer..." << endl; 
   unique_lock<mutex> lk(mu);
   if (q.size() < 10) {
     q.push(id);
     cout << id << " has been added" << endl;
   }
   else
     cout << "queue is full" << endl;
   cv.notify_all();
   
}

void consumer() {
   cout << "consumer .." << endl;
   unique_lock<mutex> lk(mu);
   while (q.size() > 0) {
       cout << q.front() << " has beem removed" << endl;
       q.pop();
   }
}

int main() {
    thread t1(producer);
    thread t2(consumer);
    
    t1.join();
    t2.join();
}