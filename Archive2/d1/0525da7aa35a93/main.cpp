#include <iostream>
#include <thread>
#include <memory>
using namespace std;
 
struct ThreadBody : std::enable_shared_from_this<ThreadBody> {
void f()
    {
    std::cerr << "Thread was there" << std::endl;
    }
};
 
int main() {
    std::shared_ptr<ThreadBody> body = std::make_shared<ThreadBody>();
    std::thread t(&ThreadBody::f, body);
    t.join();
    // your code goes here
    return 0;
}

