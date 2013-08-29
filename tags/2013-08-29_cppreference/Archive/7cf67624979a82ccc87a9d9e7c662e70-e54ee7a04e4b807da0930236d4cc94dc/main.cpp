#include <iostream>


#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


struct SYN{};
struct FIN{};
struct ACK{};


enum 
{
    fin = (1 << 0),
    syn = (1 << 1),
    ack = (1 << 2)
};


void process(SYN)      { TRACE }
void process(SYN, ACK) { TRACE }
void process(FIN)      { TRACE }
void process(FIN, ACK) { TRACE }
void process(ACK)      { TRACE }
void process()         { TRACE }


template<typename ...T>
void process(long event, T&&... tail)
{
    (event & ack) ? process(event & ~ack, ACK{}) :
    (event & syn) ? process(event & ~syn, SYN{}, std::forward<T>(tail)...) :
    (event & fin) ? process(event & ~fin, FIN{}, std::forward<T>(tail)...) :
                    process();
            
}


int main()
{
    TRACE    
    process(0);
    //process(syn|ack);
}