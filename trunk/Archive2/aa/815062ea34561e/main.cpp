#include <iostream>
#include <thread>
#include <algorithm>
#include <functional>

int main() {
    std::vector<std::function<void(void)>> workers;
    for(int i = 0; i < 10; ++i){
        workers.push_back(([](){
                std::cout << "Hi from thread\n";
            }));
    }

    std::cout << "Hi  from main!\n";
    std::for_each(workers.begin(), workers.end(), [](const std::function<void(void)>& f){
        auto t = std::thread(f);
        t.join();
    });
    return 0;
}