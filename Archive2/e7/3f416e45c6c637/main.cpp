#include <string>

class employee {
    std::string name_;
public:
    template<class String, class = std::enable_if_t<!std::is_same<std::decay_t<String>,std::string>::value>>
    void set_name( String&& name ) noexcept(std::is_nothrow_assignable<std::string&, String>::value){ 
        name_ = std::forward<String>(name); 
    }
};

int main()
{
    employee e;
    e.set_name("John");
}