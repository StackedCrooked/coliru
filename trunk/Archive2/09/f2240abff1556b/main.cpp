#include <string>
#include <memory>

class Base {
public:
    std::string Name;
};

class Derived : public Base {
public:
    std::string Address = "Initialized";
};


int main() {
    auto b_ptr = std::make_shared<Base>();
    b_ptr->Name = "Fred";
    
    auto d_ptr = std::static_pointer_cast<Derived>(b_ptr);
    
    fprintf( stdout, "Name: [%s]   Address: [%s]", 
        d_ptr->Name.c_str(),  
        d_ptr->Address.c_str() );  // Address not valid!
}

