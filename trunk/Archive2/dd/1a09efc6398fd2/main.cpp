#include <iostream>
#include <string>
#include <vector>
#include <boost/signals2/signal.hpp>

template <typename T>
struct EventSource
{
    template <typename... TT>
    class Event
    {
        friend T;
        typedef boost::signals2::signal < void(TT...) > signal_t;
        signal_t m_sig;

        void Raise(TT&&... args)
        {
            m_sig(std::forward<TT>(args)...);
        }

    public:
        boost::signals2::connection Subscribe(typename signal_t::slot_type const & s)
        {
            return m_sig.connect(s);
        }
    };
};

class Test : EventSource<Test>
{

public:
    void testRaise()
    {
        OnDataChanged.Raise("wow!");
    }

    Event<std::string const &> OnDataChanged;
};

int main()
{
    Test t;
    auto c = t.OnDataChanged.Subscribe([](std::string const & s){ std::cout << s << std::endl; });
    
    //t.OnDataChanged.Raise("ERROR");
    
    t.testRaise();
    c.disconnect();
    t.testRaise();
}
