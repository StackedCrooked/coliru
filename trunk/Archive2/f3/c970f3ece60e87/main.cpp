#include <cmath>
#include <ctime>
#include <iostream>
#include <fstream>
#include <thread>

using namespace std;


void sleep(int seconds) {
    clock_t delay = seconds * CLOCKS_PER_SEC; // convert to clock ticks
    clock_t start = clock();
    while ((clock() - start) < delay);
}

void writeToFile() {
    const int WAIT_TIME = 3;

    ofstream file;
    file.open("roots.txt");
    
    for (double i = 0; i < 100000; i++) {
        file << sqrt(i) << '\n';
    }
    
    cout << "Data has been written to the file.\n\n... pausing 3 seconds ...\n";
    sleep(WAIT_TIME);
    file.close();
}

int main() {
    cout << "main: startup\n" << flush;
    thread fileThread(writeToFile);
    cout << "main: waiting for file thread\n";
    fileThread.join();
    cout << "main: done\n";

	return (0);
}
