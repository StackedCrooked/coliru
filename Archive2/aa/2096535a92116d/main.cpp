#include <string>
#include <thread>
#include <utility>
#include <future>

std::future<std::string> method() {
        std::promise<std::string> pr;
        std::future<std::string> ft = pr.get_future();

        std::thread t(                   
            [](std::promise<std::string> p)  
            {                      
                p.set_value("z");  
            },                     
            std::move(pr)          
        );                       
        t.detach();                    

        return std::move(ft);          
}

#include <iostream>

int main() {
    std::cout << method().get() << '\n';
}
 