#include <vector>
#include <iostream>

class LoggerStream
{
public:
    template <typename ArgType>
    LoggerStream & operator<< (const ArgType &arg)
    {
        // Standard logging logic
        return *this;
    }

    template <typename DataType>
    LoggerStream & operator<< (const std::vector<DataType> &arg)
    {
        std::cout << "vec";
        return *this;
    }
/*
    template <typename DataType>
    LoggerStream & operator<< (const arma::Col<DataType> &arg)
    {
        // Specialised logging logic
        return *this;
    }
*/
    LoggerStream & operator<< (const double &arg)
    {
        // Specialised logging logic
        return *this;
    }

    // Other stuff...
};

int main()
{
    std::vector<int> v;
    LoggerStream s;
    s << v;
}