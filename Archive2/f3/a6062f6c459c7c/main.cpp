#include <string>
#include <stdio.h>
#include <memory>

class Base {
    public:
        std::string Name;

        //Note: The compiler is generating these invisibly for you:
        //Base() :Name() {}
        //~Base() {}
        //Base(const Base& r) : Name(r.Name) {}
        //Base(Base&& r) noexcept : Name(std::move(r.Name)) {}
        //Base& operator=(const Base& r) : Name(r.Name) {}
        //Base& operator=(Base&& r) noexcept : Name(std::move(r.Name)) {}
    };
    
    class Derived : public Base {
    public:
        std::string Address = "Initialized";
        Derived() = default;
        Derived(Base&& b) : Base(std::move(b)) {}
    };    
    
    int main() {
        auto b_ptr = std::make_shared<Base>();
        b_ptr->Name = "Fred";
    
        auto d_ptr = std::make_shared<Derived>(std::move(*b_ptr));
        //NOTE AT THIS POINT b_ptr POINTS TO A BASE WITH NO CONTENT
        //YOU CAN FREE IT, BUT THAT'S ALL
        b_ptr.reset(); //reset to prevent accidental errors with lack of content
    
        fprintf( stdout, "Name: [%s]   Address: [%s]", 
            d_ptr->Name.c_str(),  
            d_ptr->Address.c_str() );  // Address not valid!
    }