#include <string>
#include <thread>
#include <memory>
#include <iostream>

void some_function(int i, std::string bla) 
{ 
    std::cout << "some_function(" << i << ", " << bla << ")\n";
}

struct some_class
{
    void some_member_function(double x) const
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "some_member_function(" << x << ")\n";
    }
};

int main()
{
    std::thread t1(&some_function, 42, "the answer");
    std::thread t2;

    {
        some_class instance;
        t2 = std::thread(&some_class::some_member_function, 
                std::ref(instance), 
                3.14159);

        t2.join(); // need to join before `instance` goes out of scope
    }

    {
        auto managed = std::make_shared<some_class>();
        t2 = std::thread([managed]() 
                { 
                    managed->some_member_function(99); 
                });

        // `managed` lives on 
    }

    if (t1.joinable()) t1.join();
    if (t2.joinable()) t2.join();
}
