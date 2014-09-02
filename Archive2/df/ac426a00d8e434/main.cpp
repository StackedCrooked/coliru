#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
    std::string username;
    std::string password;

    if(argc == 3) {
        username = argv[1];
        password = argv[2];
    }
    else {
        std::cerr << "You must specify username and password arguments!"
                  << std::endl;
        return 1;
    }
    
    cout << "Username: '" << username << "' , Password: '" << password << "'" << endl;
    return 0;
}