#include <iostream>
#include <utility>
#include <memory>

class channel {
    enum state {FIRST, SECOND, THIRD};
    state state = FIRST;
public:
    void send_preamble()
    {
        state = SECOND;    
    }

    void send_payload()
    {
        if (state != SECOND) throw "bananas";
        state = THIRD;
    }
    
    void send_postamble()
    {
        state = FIRST;
    }
};
 
class base_processor
{
    std::unique_ptr<channel> channel_;
protected:
    explicit base_processor(std::unique_ptr<channel> ch) : channel_(std::move(ch)) {do_payload();}
    virtual void do_payload() = 0;
    channel* get_channel() {return channel_.get();}
public:
    void send() {do_payload();}
};
 
void base_processor::do_payload()
{
    channel_->send_payload();
}
 
struct concrete_processor : base_processor
{
    concrete_processor() : base_processor(std::unique_ptr<channel>(new channel())) {}
    void do_payload()
    {
        channel* c = get_channel();
        c->send_preamble();
        base_processor::do_payload();
        c->send_postamble();
    }
};
 
int main()
{
    concrete_processor cp;
    cp.send();
}
