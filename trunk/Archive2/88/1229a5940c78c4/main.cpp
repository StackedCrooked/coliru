#include <string>
#include <iostream>
#include <vector>
#include <iomanip>

struct S
{
    std::string firstname;
    std::string lastname;
    std::string phonenumber;
};

int main()
{
    std::vector<S> v = { { "ISRAEL", "WILKINS", "938-701-1455" }, { "BRUCE", "PERRY", "540-916-2956" }, { "VALENTIN", "RIVERS", "726-204-2377" } };
    
    for(const S& R : v)
    {
        std::cout << std::left << std::setw(30) << (R.lastname + " " + R.firstname) << std::right << R.phonenumber << std::endl;
    }
    
    return 0;   
}