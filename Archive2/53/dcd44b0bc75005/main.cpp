#include <utility>

template<typename data_type, typename functor_type>
class MyClass
{
    private:
    data_type m_data;
public:
    auto func1() -> decltype(functor_type::process(this->m_data))
    {
        return functor_type::process(m_data);
    }

    auto func2() -> decltype(functor_type::process(std::declval<data_type&>()))
    {
        return functor_type::process(m_data);
    }


};

struct Functor
{
    static int process(int& a) { return a; }
};

int main()
{
    MyClass<int, Functor> m;
    int b = m.func1();
    int c = m.func2();
}