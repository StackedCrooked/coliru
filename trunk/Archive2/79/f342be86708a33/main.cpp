#include <boost/signals2.hpp>
#include <boost/signals2/deconstruct.hpp>
#include <iostream>


#define TRACE() std::cout << __PRETTY_FUNCTION__ << std::endl



struct Sender
{
    Sender() { TRACE(); }
    ~Sender() { TRACE(); }

    using Signal = boost::signals2::signal<void()>;

    Signal signal;

private:
};


struct Receiver
{
    Receiver() { TRACE(); }

    ~Receiver() { TRACE(); }

    void receive() { std::cout << "*beep*" << std::endl; }

    friend void adl_postconstruct(boost::shared_ptr<Receiver> rx, Receiver*, Sender& tx)
    {
        tx.signal.connect(Sender::Signal::slot_type(&Receiver::receive, rx.get()).track(rx));
    }
};


int main()
{
    Sender sender;
    sender.signal();

    {
        boost::shared_ptr<Receiver> receiver = boost::signals2::deconstruct<Receiver>().postconstruct(sender);
        sender.signal();
    }

    sender.signal();
}
