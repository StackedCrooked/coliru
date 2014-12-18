#include <vector>
#include <string>
#include <iostream>

int main()
{
    std::vector<std::string> argv_storage;
    for (std::size_t i = 0; i < 10; ++i)
    {
        // I copy output of generate_rand_str() because I will need it
        // later in the code.
        argv_storage.push_back(std::to_string(i));
    }
    
    std::vector<char *> argv( argv_storage.size() + 1 );    // one extra for NULL
    for (std::size_t i = 0; i != argv_storage.size(); ++i)
    {
        argv[i] = &argv_storage[i][0];
    }
    
    //argv.back() = NULL;
    
    char** test = argv.data();
    while (*test != NULL) {
        std::cout << *(test++) << ' ';
    }
}
