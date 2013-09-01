#include <iostream>
#include <string>
#include <tbb/concurrent_queue.h>
#include <thread>

struct Message {
    std::string body;
};

tbb::concurrent_bounded_queue<Message> queue;

int main() {
    std::thread thread([] {
        Message message;
        
        queue.pop(message);
        std::cout << message.body << '\n';
        
        queue.pop(message);
        std::cout << message.body << '\n';
    });
    
    queue.push({"Hello, world!"});
    queue.push({"Bye bye, world!"});
    
    thread.join();
    return 0;
}
