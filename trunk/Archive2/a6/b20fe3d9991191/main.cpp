#include <memory>
#include <queue>
#include <boost/shared_ptr.hpp>


struct message
{
    virtual ~message() {}
    virtual message* clone() const = 0;
};

struct myMessage : message
{
    myMessage(int,int,int) {};
    myMessage* clone() const { return new myMessage(*this); }
};

#ifndef HAS_CPLUSPLUS11
    typedef boost::shared_ptr<message> msg_pointer_t;
#else
    typedef std::unique_ptr<message> msg_pointer_t;
#endif

std::queue<msg_pointer_t> messages;



#ifndef HAS_CPLUSPLUS11
    void sendMessageA(const message& msg)
    {
        msg_pointer_t p(msg.clone());
        messages.push(p);
    }
    
    void sendMessageB(const msg_pointer_t& p)
    {
        messages.push(p);
    }
#else
    template <typename T, typename... Args>
    void sendMessageC(Args... args)
    {
        messages.emplace(new T(args...));
    }
#endif

int main()
{
    #ifndef HAS_CPLUSPLUS11
        // Current usage.
        // 
        // Wasteful due to the need for clone, but that's
        // the way the API is.
        sendMessageA(myMessage(3,4,5));
        
        // Better, C++03-compliant usage which doesn't need
        // copies, though there's still a refcount increment
        // and I don't like the verbosity at the call site.
        sendMessageB(msg_pointer_t(new myMessage(3,4,5)));
    #else
        // Ideal, right? May be able to sell this if I'm
        // migrating to C++11 anyway.
        sendMessageC<myMessage>(3,4,5);
    #endif
}
