#include <thread>
#include <iostream>
#include <chrono>
#include <atomic>
#include <mutex>
#include <vector>
#include <string>
#include <future>

using namespace std;

string getUrl(string url) {
    string result = "Data: " + url;
    this_thread::sleep_for(chrono::milliseconds(100));
    return result;
}

int main() {
    auto future = async(getUrl, "hello world");
    string example = future.get();
    cout << example << endl;
    return 0;
}