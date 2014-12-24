#include <cstdio>
#include <iostream>
 
int main()
{
    const char* file_name = "C:\\a.txt";
    int ret_code = std::remove(file_name);
    if (ret_code == 0) {
        std::cout << "File was successfully deleted\n";
    } else {
        std::cerr << "Error during the deletion: " << ret_code << '\n';
    }
}