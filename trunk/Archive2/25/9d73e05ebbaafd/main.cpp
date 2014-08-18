#include <iostream>
#include <thread>
#include "unistd.h"

using namespace std;
thread *timerThread;
bool interrupted = false;

void callBackFunc(int anyParam) {
    // Perform your timeout handling
    cout << "Callback handling with parameter input " << anyParam << endl;
}

void timerThreadTask(int sleepLengthInMilliSec, void (*callBackFuncPtr)(int anyParam)) {
    // Thread procedures
    int counter = 100;
    int sleepIntervals = sleepLengthInMilliSec / counter;
    while (counter-- > 0) {
        if (interrupted == true) { // Interrupted
            cout << "Sleep interrupted because a new port event is received." << endl;
            interrupted = false;   // Kill thread
            delete timerThread;
            timerThread = NULL;
            return;
        }
        usleep(sleepIntervals);
    }
    callBackFuncPtr(10);   // Timeout, execute callback
}

void onPortEventReceived() {
    // If a message is received in time, then a thread
    // will still be executing. The timer is to be
    // restarted.
    if (timerThread != NULL) {
        interrupted = true;
    }
    int sleepLengthInMilliSec = 1000; // Set timer
    // Starts a timer thread (**** When this line is commented, the compile will success but this will surely be meaningless)
    timerThread = new thread(timerThreadTask, sleepLengthInMilliSec, callBackFunc);
}

int main() { }