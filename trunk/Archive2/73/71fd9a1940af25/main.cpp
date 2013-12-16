#include <iostream>
#include <string>

int main() {
    std::string text = "The quick brow fox jumps over a lazy dog";
    std::string::size_type start = 0, end = 0;
    
    while (end != std::string::npos) {
        // find space in text from start, store it in end
        end = text.find (' ', end);
        // output end - start chars from text starting from start
        std::cout << text.substr (start, end - start) << std::endl;
        // new start is now is one char after space
        start = end + 1;
    }
    
    /*
     * now you can see that there are a fuck ton of std::s here, the
     * 'using namespace std;' line at the top could allow you to skip each
     * of them.
     */
    
    return 0;
}
