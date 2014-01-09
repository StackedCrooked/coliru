#include <iostream>
#include <string>


struct user_string : std::string
{
    using std::string::string;
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


user_string input();

void process(sanitized_string);


int main()
{
    process(input());
}
