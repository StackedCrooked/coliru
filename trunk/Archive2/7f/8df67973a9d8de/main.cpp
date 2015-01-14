#include <sstream>
#include <string>

class SmartStream
{
public:
    template <typename F> friend F &operator << (F &in, float f)
    {
        in.type ("f");
        in.m_buf.str ("");
        in.m_buf << f;          // This causes a 'recursive' compile call
        in.add (in.m_buf.str ());
        return in;
    }

protected:
    std::ostringstream m_buf;

    void type(const std::string &_type) {};
    void add(const std::string &) {};
};

int main()
{
    SmartStream s;
    s << 42.f;
}