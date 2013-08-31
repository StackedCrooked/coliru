#include <iostream>
#include <string>

#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


struct active_open {};
struct passive_open {};
struct receive_syn {};
struct receive_ack {};

struct closed {};
struct listen {};
struct syn_received {};
struct syn_sent {};


struct send_syn{};
struct send_ack{};


struct Impl
{
    template<typename Event, typename From, typename To>
    void enter_state(Event event, From from, To to)
    {
        TRACE
        do_enter_state(event, from, to);
    }
    
    void do_enter_state(passive_open, closed, listen)
    {
    }
    
    void do_enter_state(active_open, closed, listen)
    {
    }
    
    void do_enter_state(send_syn, closed, syn_sent)
    {
    }
};

int main()
{
    Impl i;
    i.enter_state(active_open{}, closed{}, listen{});
    i.enter_state(passive_open{}, closed{}, listen{});
    i.enter_state(send_syn{}, closed{}, syn_sent{});
}