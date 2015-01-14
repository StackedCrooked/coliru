#include <iostream>
#include <vector>

template<typename T> struct tag {};

class A
{
public:
    struct TAll {};
    constexpr static TAll All{};

    typedef std::vector<int> TVec;
    static TVec m_sVec;

    static TVec::iterator begin() { return m_sVec.begin(); }
    static TVec::iterator end() { return m_sVec.end(); }
};

A::TVec A::m_sVec;
const A::TAll A::All;

A::TVec::iterator begin(A::TAll all) { return A::begin(); }
A::TVec::iterator end(A::TAll all) { return A::end(); }

int main()
{
    A::m_sVec.push_back(1);
    A::m_sVec.push_back(2);
    A::m_sVec.push_back(3);

    for (auto a : A::All) {
    //for (auto a = begin(A::All); a != end(A::All); a++) {
        std::cout << a << std::endl;
    }

    return 0;
}