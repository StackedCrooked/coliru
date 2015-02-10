#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

int main()
{
        int yay = open("somefolder", 0);
        std::cout << yay << "\n";
        close(yay);
        return 0;
}
