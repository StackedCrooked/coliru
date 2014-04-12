#include <iostream>
#include <string>

void vowelfinder(std::string fullname);


int main()
{
    std::string nfirst, nlast;

    std::cout << "Enter Your First Name: ";
    std::cin >> nfirst;
    std::cout << "Enter Your Last Name: ";
    std::cin >> nlast;

    std::string nfull = nfirst + " " + nlast;

    vowelfinder(nfull);

}



void vowelfinder(std::string fullname)
{
    std::size_t pos = fullname.find('a'); //first 'a' found
    if(pos != std::string::npos) //-1 if you want
    {
        std::cout << "The first 'a' vowel was found at position: " << pos << std::endl;
    }
    else
    {
        std::cout << fullname << " contains no 'a'." << std::endl;
    }
}