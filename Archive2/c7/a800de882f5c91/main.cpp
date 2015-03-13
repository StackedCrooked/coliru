#include <streambuf>
#include <iostream>
#include <string>
#include <boost/utility/string_ref.hpp> 
#include <boost/timer/timer.hpp>
#include <sstream>
#include <cstring>
 
template<typename charT, std::size_t N, 
         typename traits = std::char_traits<charT>>
class fixed_streambuf : public std::basic_streambuf<charT, traits>
{
public:
    fixed_streambuf() 
    {
        this->setp(data_, data_ + N);
        this->setg(data_, data_, data_);
    }
    
    boost::basic_string_ref<charT, traits> str()
    {
        return boost::basic_string_ref<charT, traits>(this->gptr(), this->in_avail());
    }
    
    const boost::basic_string_ref<charT, traits> str() const
    {
        return boost::basic_string_ref<charT, traits>(this->gptr(), this->in_avail());
    }
    
    constexpr std::streamsize capacity() noexcept
    {
        return N;
    }
    
private:
    using typename std::basic_streambuf<charT, traits>::char_type;
    char_type data_[N]{};
};
 
using namespace std;
 
int main(int argc, char* argv[])
{
    {
        boost::timer::auto_cpu_timer t;
        int i = 10000;
        while(i--)
        {
            fixed_streambuf<char, 4096> sbuf;                
            ostream os(&sbuf);            
            int j = 300;            
            while(j--)
            {
                os << "Hello!" << 1 << 2 << 3;
            }
        }
    }

    {
        boost::timer::auto_cpu_timer t;
        int i = 10000;
        while(i--)
        {
            stringstream ss;
            int j = 300;            
            while(j--)
            {
                ss << "Hello!" << 1 << 2 << 3;
            }
        }
    }

 
    return 0;
}