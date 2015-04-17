#include <functional>
#include <iostream>
#include <streambuf>
#include <tuple>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/adapted.hpp>
#include <boost/timer/timer.hpp>
#include <sstream>

class null_streambuf final : public std::streambuf
{
public:
    int overflow(int c) override
    { 
        return c; 
    }
};

class attribute
{
public:
    virtual void start(std::ostream& strm) = 0;
    
    virtual void end(std::ostream& strm) = 0;
    
    virtual bool do_evaluate() = 0;
    
    template<typename... Tp>
    void evaluate(std::ostream& strm, const std::tuple<Tp...>& context)
    {
        start(strm);
        if (do_evaluate())
        {
            boost::fusion::for_each(context, [&strm](const auto& v){ strm << v; });
        }
        //end(strm);    
    }
};

class context_discriminating_attribute final : public attribute
{
public:
    context_discriminating_attribute() {}

    void start(std::ostream& strm) override
    {
        flags_ = strm.flags();
        strm << "666";
    }
    
    void end(std::ostream& strm) override
    {
    //    strm.flags(flags_);
    }
    
    bool do_evaluate() override
    {
        return false;
    }
    
private:
    std::ios::fmtflags flags_;
};

int main(int argc, char* argv[])
{
    context_discriminating_attribute attr;
    attribute* pattr = &attr;
    {
        boost::timer::auto_cpu_timer t;
        null_streambuf null_streambuf;
        std::ostream null_stream(&null_streambuf);    
        for (int i = 0; i < 100000; i++)
        {
            pattr->evaluate(null_stream, std::make_tuple(1, 2, "test", 3.5, 4.666, "ho!"));
        }
    }
    {
        boost::timer::auto_cpu_timer t;
        std::stringstream ss;        
        for (int i = 0; i < 100000; i++)
        {
            ss << 1 << 2 << "test" << 3.5 << 4.666 << "ho!";
        }
    }
    return 0;
}