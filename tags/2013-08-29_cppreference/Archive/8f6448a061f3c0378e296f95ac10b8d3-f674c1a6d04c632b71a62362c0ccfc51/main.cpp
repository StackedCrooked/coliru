#include <thread>
#include <iostream>

void helloWhere(){
    std::cout << "Où ";
}

void helloIs(){
    std::cout << "est ";
}

void helloTosh(){
    std::cout << "Tosh ? ";
}

int main(){
    std::thread t1(helloWhere);
    std::thread t2(helloIs);
    std::thread t3(helloTosh);
    t1.join();t2.join();t3.join();

    return 0;
}