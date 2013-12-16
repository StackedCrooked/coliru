#include <iostream>
#include <fstream>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

struct Monkey
{
    uint32_t num;
    float* arr;

    Monkey() : num(0u), arr(nullptr) {}

    Monkey(Monkey const&) = delete;
    Monkey& operator=(Monkey const&) = delete;
    ~Monkey() { delete[] arr; }
};

namespace boost
{
    namespace serialization
    {
        template<class Archive>
        void serialize(Archive & ar, Monkey& m, const unsigned int version)
        {
            ar & m.num;
            if (Archive::is_loading::value)
            {
                assert(m.arr == nullptr);
                m.arr = new float[m.num];
            }
            ar & make_array<float>(m.arr, m.num);
        }
    }
}

int main(int argc, char* argv[])
{
    const char* name = "monkey.txt";
    {
        Monkey m;
        m.num = 10;
        m.arr = new float[m.num];
        for (uint32_t index = 0; index < m.num; index++)
            m.arr[index] = (float)index;

        std::ofstream outStream(name, std::ios::out | std::ios::binary | std::ios::trunc);
        boost::archive::binary_oarchive oar(outStream);
        oar << (m);
    }

    Monkey m;
    std::ifstream inStream(name, std::ios::in | std::ios::binary);
    boost::archive::binary_iarchive iar(inStream);
    iar >> (m);

    std::copy(m.arr, m.arr + m.num, std::ostream_iterator<float>(std::cout, ";"));
}