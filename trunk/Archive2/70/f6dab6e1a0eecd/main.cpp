#include <iostream>
#include <string>


struct user_string : private std::string
{
    using std::string::string;
    friend class sanitized_string;
};


struct sanitized_string : std::string
{
    /*implicit*/ sanitized_string(user_string us) :
        std::string(std::move(us))
    {
        sanitize();
    }
    
private:
    void sanitize() { /*...*/ }
};


user_string input() { return "bobby"; }

void process(sanitized_string) {}


int main()
{
    process(input());
}
