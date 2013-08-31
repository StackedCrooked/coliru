#include <iostream>
#include <string>
#include <vector>


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

class myVector
{
public:
    myVector( const std::initializer_list< int >& lst )
    {
        v = lst;
    }
private:
    std::vector< int > v;
};

class UseConstructorAsInitList
{
public:
    UseConstructorAsInitList() = default;
    UseConstructorAsInitList( int a, int b ) { m_a = a ; m_b = b; }
    void Print() { std::cout<< m_a<<" "<<m_b<<std::endl; }
    UseConstructorAsInitList( const UseConstructorAsInitList& ) = delete;
    UseConstructorAsInitList& operator=( const UseConstructorAsInitList& ) = delete;
private:
    int m_a = 23;
    int m_b = 24;
};

int main()
{
    std::vector<int> v = { 1, 2, 3, 4 };
    auto vcopy = v;
    UseConstructorAsInitList a = {3, 4 }; //uses constructor!
    UseConstructorAsInitList b;
    
    a.Print();
    b.Print();
    // compiler error UseConstructorAsInitList c = a;
    //compiler error a = b;
}
