#include <iostream>
#include <string>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>

struct some_passive_data_structure
{
    int foo;
    std::string bar;
};

class some_active_data_structure
{
public:
    some_active_data_structure(int foo, const std::string& bar)
        : pod_{foo, bar}
    {}

    int get_foo() const
    {
        return pod_.foo;
    }
    
    void set_foo(int foo)
    {
        pod_.foo = foo;
    }
    
    std::string get_bar() const
    {
        return pod_.bar;
    }
    
    void set_bar(const std::string bar)
    {
        pod_.bar = bar;
    }
    
    template<typename Visitor>
    void accept(const Visitor& v)
    {
       v(pod_);
    }
    
private:
    some_passive_data_structure pod_;
};

BOOST_FUSION_ADAPT_STRUCT(
    some_passive_data_structure,
    (int, foo)
    (std::string, bar)
)

struct printer
{
    template<typename T>
    void operator()(const T& t) const
    {
        std::cout << t << std::endl;    
    }  
};

struct printing_visitor
{
    template<typename T>
    void operator()(const T& t) const
    {
        boost::fusion::for_each(t, printer());
    }
};

int main(int argc, char* argv[])
{
    some_active_data_structure data{666, "hello kitty"};
    data.accept(printing_visitor());    
    
    return 0;
}
