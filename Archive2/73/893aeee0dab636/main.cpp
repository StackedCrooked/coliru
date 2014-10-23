#include <iostream>
#include <vector>
#include <cstdio>
#include <map>
#include <iterator>
#include <algorithm>
#include <thread>
#include <mutex>
#include <atomic>
#include <time.h>
#include <array>
#include <unistd.h>
#include <math.h>
#include <condition_variable>
#include <deque>

using namespace std;

long MAX = 100;
//mutex m;
atomic_int num(0);

mutex mpush;
mutex mpop;
condition_variable cv_push;
condition_variable cv_pop;

//class myQueue
//{
////    public:
////        void push(int val)
////        {
////            unique_lock<mutex> lk(mpush);
////            data.push_back(val);   
////            lk.unlock();
////            cv.notify_one();
////        }
////        
////        int pop()
////        {
////            unique_lock<mutex> lk(mpush);
////            cv.wait(lk, []{return true;});
////
////            int val = data.back();
////            data.pop_back();
////            return val;
////            lk.unlock();
////        }    
// 
//    private:
//        vector<int> data;
//};


//myQueue myQueue; 
deque<int> dq;

void producent(int id)
{
    
    while(true)
    {
        unique_lock<mutex> lk(mpush);
        cv_push.wait(lk, []{ if (dq.size() < MAX) return true; else return false;});
        
        time_t t = time(0);
        dq.push_front((int) t);   

        cout << "Produced value: " << t << endl;

        lk.unlock();
        cv_pop.notify_one();
        
//        sleep(1);
    }
    
}

void consumer(int id)
{
    
    while(true)
    {
        unique_lock<mutex> lk(mpop);
        cv_pop.wait(lk, []{ if (dq.size() > 0) return true; else return false;});
        
        
        int val = dq.back();
        dq.pop_back();
        cout << "GOT value: " << val << endl;
        lk.unlock();
        cv_push.notify_one();
        
        sleep(1);
        
    }
    
}

int main()
{

    
    cout << "START" << endl;
    
    
    int i = 1;
    thread t1(producent, i); //, mList);
    i = 2;
    thread t2(consumer, i); //, mList);
    i = 3;
    thread t3(consumer, i); //, mList);
//    i = 4;
//    thread t4(author, i); //, mList);
//    i = 5;
//    thread t5(author, i); //, mList);
    t1.join();
    t2.join();
    t3.join();
//    t4.join();
//    t5.join();
    

	return 0;
}
