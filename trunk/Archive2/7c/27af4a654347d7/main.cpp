#include <vector>
#define UNUSED(x) (void)x // stops warnings that variable was not used
int main()
{
    char buffer[] = "hello"; UNUSED(buffer);
    //char * X = new decltype(buffer){std::begin(buffer), std::end(buffer)}; // doesn't work
    //char* Y = new decltype(buffer){buffer}; UNUSED(Y);  // doesn't work
    //char* Z = new decltype(buffer){"hi"}; UNUSED(Z); // doesn't work
    char* Y = new char[3]{'h', 'i'}; UNUSED(Y); // works
    
    std::vector<char> x { std::begin(buffer), std::end(buffer) }; // works
    //std::vector<char> y { buffer }; // doesn't work
    //std::vector<char> z { "hi" }; // doesn't work
    std::vector<char> w {'h', 'i'}; // works
}
