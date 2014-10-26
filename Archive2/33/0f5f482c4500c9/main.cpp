#include <map>
#include <iostream>

template <typename T1, typename T2>
class SampleClass {

public:
    SampleClass() = default;

    void Add(const T1 &key, const T2 &value)
    {
        database[key] = value;
    }

    typename std::map<T1, T2>::const_iterator cbegin() const { return database.cbegin(); }
    typename std::map<T1, T2>::const_iterator cend() const { return database.cend(); }


private:
    std::map<T1, T2> database;
};

template <typename T1, typename T2> 
std::ostream &operator << (std::ostream &os, SampleClass<T1, T2> &rhs)
{
    for(auto el = rhs.cbegin(); el != rhs.cend(); el++)
        os << el->first << " " << el->second << std::endl;
    return os;
}

int main()
{
    SampleClass<int, int> s;
    std::cout << s;
}