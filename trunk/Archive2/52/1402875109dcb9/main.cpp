// test.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>

class copy_constructible
{
public:
    copy_constructible()
    {
        std::cout << "default constructor" << std::endl;
    }

    copy_constructible(const copy_constructible& /*other*/)
    {
        std::cout << "copy constructor" << std::endl;
    }

    copy_constructible& operator=(const copy_constructible& /*other*/)
    {
        std::cout << "= operator" << std::endl;
        return *this;
    }
};

class container
{
public:
    container() :
        m_data(5)
    {
    }

    const std::vector<copy_constructible>& get() const
    {
        return m_data;
    }

private:
    std::vector<copy_constructible> m_data;
};

int main(int argc, char* argv[])
{
    container c;

    std::cout << "C++ 03 style" << std::endl;
    const std::vector<copy_constructible>& data1 = c.get();

    std::cout << "auto style" << std::endl;
    auto data2 = c.get();

    std::cout << "auto& style" << std::endl;
    auto& data3 = c.get();

    return 0;
}

