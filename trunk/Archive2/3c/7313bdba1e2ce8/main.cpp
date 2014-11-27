#include <mutex>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void Init();

struct Global {
    Global() { Init(); }
};

struct OnceFlagWrapper {
    OnceFlagWrapper() { cout << "creating once_flag" << std::endl;}
    once_flag flag;
};

Global global;

OnceFlagWrapper o;

void Init() {
    call_once(o.flag, []{  cout << "hello" << endl;  });
}

int main() {
    Init();
}