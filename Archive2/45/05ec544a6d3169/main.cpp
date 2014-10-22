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
#define LIMIT 1000000

long int i=0;

void decme()
{
    for (long t=LIMIT; t > 0; t--) {
        i--;
        cout << "DEC:" << i << endl;
    }
}

void incme()
{
    for (long t=LIMIT; t > 0; t--) {
        i++;
        cout << "INC:" << i << endl;
    }
}

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    
    thread t1(incme);
    thread t2(decme);

    t1.join();
    t2.join();
return 0;
}

