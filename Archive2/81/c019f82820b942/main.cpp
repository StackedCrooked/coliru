/* 
 * File:   main.cpp
 * Author: deszcz
 *
 * Created on October 22, 2014, 9:18 AM
 */
using namespace std;
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

#define NUM 5
mutex widelce[NUM];
mutex mcout;

void filozofek( int id )
{
    int lewy=id;
    int prawy=id+1;

    if  (prawy==NUM+1)
    {
        prawy=0;
    }
    
    mcout.lock();
    cout << id << " siada" << endl;
    mcout.unlock();

    while (true)
    {
        mcout.lock();
        cout << id << " mysli" << endl;
        mcout.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        widelce[lewy].lock();
    
        if (widelce[prawy].try_lock())
        {
            mcout.lock();
            cout << id << " spożywa" << endl;
            mcout.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            widelce[prawy].unlock();
            widelce[lewy].unlock();
        }
        else
        {
            widelce[lewy].unlock();
        }
    }
}


int main(int argc, char** argv) {
    
    vector<thread> vec;
    for(int i=0; i<NUM-1; i++)
        vec.push_back(thread(filozofek, i));
        vec[0].join();
    return 0;
}