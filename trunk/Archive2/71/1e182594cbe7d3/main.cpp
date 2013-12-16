#include <iostream>
using namespace std;

#include <future>
#include <thread>
#include <string>

class Stub {
    public:
	virtual future<string> method() = 0;
};

class Child: public Stub {
	public:
	future<string> method() {
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
};

int main() {
	// your code goes here
	Child c;
	auto s = c.method().get();
    std::cout << s << std::endl;
	return 0;
}