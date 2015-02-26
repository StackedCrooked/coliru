//============================================================================
// Name        : flow123d-test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <typeinfo>
#include <string>

using namespace std;


// return smallest amount of time measured by clock() function
double clock_resolution() {
    clock_t t1,t2;

    t2=t1=clock();
    while (t1 == t2) { clock(); t2=clock();}
    cout << "tick: " << (t2-t1) << endl;
    double min_time_step = 1000.0 * (t2-t1) / CLOCKS_PER_SEC;
    return min_time_step;
}

double chrono_resolution () {
    chrono::time_point<chrono::system_clock> t1, t2;
	t2=t1=chrono::system_clock::now();
	while((t2-t1).count() == 0) { t2 = chrono::system_clock::now();}
	cout << "tick: " << (t2-t1).count() << endl;
	double min_time_step = 1000.0 * (t2-t1).count() / CLOCKS_PER_SEC;
	return min_time_step;
}

double chrono_high_resolution () {
	chrono::time_point<chrono::high_resolution_clock> t1, t2;
	t2=t1=chrono::high_resolution_clock::now();
	while((t2-t1).count() == 0) { t2 = chrono::high_resolution_clock::now();}
	cout << "tick: " << (t2-t1).count() << endl;
	double min_time_step = 1000.0 * (t2-t1).count() / CLOCKS_PER_SEC;
	return min_time_step;
}

double chrono_steady_resolution () {
	chrono::time_point<chrono::steady_clock> t1, t2;
	t2=t1=chrono::steady_clock::now();
	while((t2-t1).count() == 0) { t2 = chrono::steady_clock::now();}
	cout << "tick: " << (t2-t1).count() << endl;
	double min_time_step = 1000.0 * (t2-t1).count() / CLOCKS_PER_SEC;
	return min_time_step;
}

template <class Clock> void display_precision(char * name) {
    typedef std::chrono::duration<double, std::nano> NS;
    NS ns = typename Clock::duration(1);
    printf("%s, (%s): ", name, typeid(Clock).name());
    cout << ns.count() << " ns" << endl;
}

int main(void) {
    cout << "clock_resolution:          " << clock_resolution() << endl<< endl;
    cout << "chrono_resolution:         " << chrono_resolution() << endl<< endl;
    cout << "chrono_high_resolution:    " << chrono_high_resolution() << endl<< endl;
    cout << "chrono_steady_resolution:  " << chrono_steady_resolution() << endl<< endl;


    return 0;
}
