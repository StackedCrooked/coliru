#include <iostream>
#include <string>
#include <thread>

class Tkoko111
{
public: Tkoko111(){}
~Tkoko111(){}

};

void threadQueue(std::shared_ptr<Tkoko111 > queue)
{
(void)queue;
}

void test(){
for (int i = 0; i < 90000; ++i)
{
std::shared_ptr<Tkoko111> q(new Tkoko111() );
std::thread t1(threadQueue,q);
t1.join();
}
}

int main(){test();::std::cout<<"ok"<<::std::endl;return 0;}