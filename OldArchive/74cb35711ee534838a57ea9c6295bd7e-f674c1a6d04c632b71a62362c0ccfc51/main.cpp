#include <sstream>
#include <string>


class MakeString
{
public:
    template <typename T>
    MakeString & operator<<(const T & datum)
    {
        mBuffer << datum;
        return *this;
    }
    operator std::string() const
    {
        return mBuffer.str();
    }
private:
    std::ostringstream mBuffer;
};



#include <iostream>

int main()
{
    typedef MakeString SS;
    std::cout << std::string(SS() << "Hello " << 123) << std::endl;
}





