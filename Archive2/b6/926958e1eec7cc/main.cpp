#include <thread>
#include <iostream>

class scoped_thread
{
std::thread t;
public:
explicit scoped_thread(std::thread t_):t(std::move(t_))
{
    std::cout<<"here I'm"<<std::endl;
    if(!t.joinable())
        throw std::logic_error("No thread");
}

~scoped_thread()
{

    t.join();
}

scoped_thread(scoped_thread const&)=delete;
scoped_thread& operator=(scoped_thread const&)=delete;
};


void foo(){
std::cout<<"foo"<<std::endl;    
}

scoped_thread t1((std::thread(foo)));

int main() {}