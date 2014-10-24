#include <iostream>
#include <functional>


class TruckProducer 
{
std::function<void()> truckReceiver;
public:
    TruckProducer(std::function<void()> _truckReceiver) : truckReceiver(_truckReceiver) 
    {
        truckReceiver();
    };
};    

void p() {
    std::cout<<"Produced!\n";
};

int main(int nArgs, char *args[]) {
    std::cout<<"Hello!";
    TruckProducer pro(p);
    return 0;
}