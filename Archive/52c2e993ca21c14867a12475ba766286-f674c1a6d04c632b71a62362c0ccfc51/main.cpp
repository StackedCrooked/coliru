#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

void hworld(int id, std::mutex& m) {
    
    std::lock_guard<std::mutex> lg{m};
    
    for(int j=0; j<5; ++j) {
        std::cout << " hworld " << id;
    }
    std::cout << std::endl;
}

int main()
{
    std::mutex m;

    std::thread t1(hworld, 1, std::ref(m));
    std::thread t2(hworld, 2, std::ref(m));
    
    t1.join();
    t2.join();

}
