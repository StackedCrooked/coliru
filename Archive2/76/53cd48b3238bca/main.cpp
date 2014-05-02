#include <thread>

class MyClass {
private:
    std::thread thread;
    void run();
public:
    ~MyClass();
    void start();
};

MyClass::~MyClass() {
    if (thread.joinable())
        thread.join();
}

void MyClass::run() {
    //do stuff
}

void MyClass::start() {
    thread = std::thread(&MyClass::run, this);
}

int main() {
    MyClass obj{};
    obj.start();
}
