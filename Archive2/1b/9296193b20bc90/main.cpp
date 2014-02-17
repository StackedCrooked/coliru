#include <string>

struct detail
{
private:
    struct A
    {
        A(A const&) = delete;
        A(A&&) = delete;
        
        A(int) {}
        A(std::string) {}
        
        void mutate() {}
    };
    
    friend const A make_A(int);
    friend       A make_A(std::string);
};

const detail::A make_A(int p) { return {p}; }
      detail::A make_A(std::string p) {return {p}; }
      

#include <type_traits>

int main()
{
    auto const& x = make_A(42); // x is immutable
    auto&& y = make_A("hello"); // y is mutable
    
    auto&& x1 = make_A(42); // x1 is a `A const&&`
    x1.mutate(); //error
    auto& x2 = make_A(42); // x2 is a `A const&`
    x1.mutate(); //error
}