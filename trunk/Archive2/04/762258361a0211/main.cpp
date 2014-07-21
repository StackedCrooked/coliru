#include <iostream>
#include <ostream>
#include <sstream>
#include <stack>
#include <string>

thread_local std::stack<std::ostream*> couts({&std::cout});

class cout_guard {
public:
    cout_guard(std::ostream& cout) {
        couts.push(&cout);
    }

    ~cout_guard() {
        couts.pop();
    }
};

std::ostream& cout() {
    return *couts.top();
}

void f() {
    cout() << "Hello, world!\n";
}

std::string g() {
    std::ostringstream stream;
    cout_guard g(stream);
    f();
    return stream.str();
}

int main() {
    f();
    cout() << g().size();
}
