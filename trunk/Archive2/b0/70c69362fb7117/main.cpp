#include <iostream>
#include <string>
#include <vector>

class myString : public std::string{

public:

    using std::string::string;
    void translate(){
        std::string phrase(this->c_str(), this->length());

        phrase += "2";

        *this = phrase;
    }    
};

int main()
{
    myString m = "test";
    std::cout << m << '\n';
    m.translate();
    std::cout << m << '\n';
}
