#include <functional>
#include <future>
#include <iostream>


class Session
{
public:
    Session(Session& lower_layer_session) :
        lls(&lower_layer_session),
        notify([]{ return std::async([]{});})
    {
        // We want the session "stack" to be broken down from top to bottom.
        // We achieve this by hooking into the notify function, which is called
        // before close_impl() (see implementation of close method below).
        auto copy = lower_layer_session.notify;
        
        lower_layer_session.notify = [=]() -> std::future<void> {

            // close self first
            std::shared_future<void> f1 = this->close();
            
            // call the old notify function
            std::shared_future<void> f2 = copy();
            
            // wait for the combined result
            return std::async([=]{
                f1.wait();
                f2.wait();
            });
            
        };
    }

    std::future<void> close()
    {
        // first notify higher layer sessions that we are closing
        // (they will react by calling close on themselves. this  will
        // recurse until the top-level session is reached)
        std::shared_future<void> f1 = notify();
        
        // then close self
        std::shared_future<void> f2 = close_impl();
         
        return std::async([=] {
            f1.wait();
            f2.wait();
        });
    }
    
protected:
    Session() : lls(), notify([]{ return std::async([]{});}) {}
    
private:
    virtual std::future<void> close_impl() = 0;
    Session* lls;
    std::function<std::future<void>()> notify;
};


struct L1 : Session
{
    L1() : Session() {}
    
    std::future<void> close_impl()
    {
        return std::async([]{
            std::cout << "Closing L1" << std::endl;
        });
    }
};


struct L2 : Session
{
    L2(L1& l1) : Session(l1) {}
    
    std::future<void> close_impl()
    {
        return std::async([]{
            std::cout << "Closing L2" << std::endl;
        });
    }
};


struct L3 : Session
{
    L3(L2& l2) : Session(l2) {}
    
    std::future<void> close_impl()
    {
        return std::async([]{
            std::cout << "Closing L3" << std::endl;
        });
    }
};


int main()
{
    L1 layer1;
    L2 layer2(layer1);
    L3 layer3(layer2);
    layer1.close().get();
}
