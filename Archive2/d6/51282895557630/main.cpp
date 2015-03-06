#include<memory>
#include <map>
#include <utility>

template <typename T, typename U>
class create_map
{
private:
    std::map<T, U> m_map;
public:
    create_map(T key, U val)
    {
        m_map.emplace(std::move(key), std::move(val));
    }

    create_map&& operator()(T key, U val) &&
    {
        m_map.emplace(std::move(key), std::move(val));
        return std::move(*this);
    }

    operator std::map<T, U>() &&
    {
        return std::move(m_map);
    }
};

class MyFieldInterface
{
public:
    int m_Size;
    virtual ~MyFieldInterface() = default;
};

template <typename T>
class MyField : public MyFieldInterface {
    T m_Value; 
};

using DWORD = unsigned int;
using WORD = unsigned short;


std::map<DWORD, std::unique_ptr<MyFieldInterface>> mymap = create_map<DWORD, std::unique_ptr<MyFieldInterface>>(1, std::make_unique<MyField<DWORD>>())(2, std::make_unique<MyField<char>>())(3, std::make_unique<MyField<WORD>>());

int main(){}