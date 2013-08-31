#include <iostream>
#include <tuple>


template<typename T, typename /*disambiguator*/>
struct StrongTypedef
{
    StrongTypedef(const T & data = T()) : data_(data) {}    
    operator const T&() const { return data_; }        
    
    T data_;
};


#define STRONG_TYPEDEF(Type, Name) \
    typedef StrongTypedef<Type, struct Type##_> Name;
    
    

STRONG_TYPEDEF(unsigned long, Id)
STRONG_TYPEDEF(std::string, Title)
STRONG_TYPEDEF(std::string, Description)


// A "record" is a tuple where are elements are of different type.
// This enables access by type instead of index.
template<typename ...Args>
auto make_record(Args && ...args) -> std::tuple<Args...>
{
    static_assert(all_types_are_different<Args>::value, "The argument list must not contain two objects of same type.")
    return std::make_tuple(std::forward<Args>(args)...);

}

int main()
{
    auto book = make_record(Id(120),
                            Title("Exploring the boundaries of the universe, a biography."),
                            Author("Your mom"));
                            
    auto title = get<Title>(book);
    auto author = get<Author>(book);
    
    std::cout << title << " was written by " << author << "." << std::endl;        
}
