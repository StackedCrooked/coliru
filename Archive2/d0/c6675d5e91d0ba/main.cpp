// Example program
#include <iostream>
#include <string>
#define SIZE 50

bool checkLength (char password[]) {
    int numChar = 0;
    bool validlength = false;

    for (int cnt = 0; cnt < SIZE; cnt++) {
        if (password [cnt] == '\0') {
            numChar = cnt;
    	    break ;
		}
        std::cout << "number cout : " << cnt << "pass " << password << std::endl; // rafal
    }

    if ((numChar >= 6) && (numChar <= 13))    
        validlength = true;

	if (!validlength){
		 std::cout << "Error, password must be at least 6 characters long.\n";
	}

    return validlength;
}

int main() {
    char pass[] = "rafal";
    std::cout << pass << std::endl
              << std::boolalpha << checkLength(pass) << std::endl
              << pass << std::endl;
}
