#include <iostream>


template<typename T, typename /*disambiguator*/>
struct StrongTypedef
{
    StrongTypedef(const T & data = T()) : data_(data) {}    
    operator const T&() const { return data_; }        
    
    T data_;
};


#define STRONG_TYPEDEF(Type, Name) \
    typedef StrongTypedef<Type, struct Type##_> Name;
    
    

STRONG_TYPEDEF(int, Id);
STRONG_TYPEDEF(std::string, Title);
STRONG_TYPEDEF(std::string, Description);


int main()
{
    auto book = make_record(Title("Exploring the boundaries of the universe, a biography."), Author("Your mom"));
    auto title = get<Title>(book);
    auto author = get<Author>(book);
    std::cout << title << " was written by " << author << "." << std::endl;
}