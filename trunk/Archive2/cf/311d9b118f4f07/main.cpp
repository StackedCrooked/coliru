#include <iostream>
#include <list>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>
#include <memory>
#include <regex>
#include <future>
#include <set>
#include <thread>
#include <vector>
#include <atomic>
#include <iostream>

class Test
{
public:
    Test() {}
    ~Test() { printf("Destroy!\n"); }

    void run()
    {
        printf("Called\n");
    }
};


int main()
{
        std::shared_ptr<Test> test = std::make_shared<Test>();
        std::thread th(std::bind(&Test::run, test));
        th.join();


    return EXIT_SUCCESS;
}

