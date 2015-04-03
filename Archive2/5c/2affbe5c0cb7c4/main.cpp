#include <iostream>
#include <string>
#include <functional>


typedef std::function<void(std::string, std::function<bool(void)>)> itFunc;
void describe(std::string, std::function<void(itFunc)> describeCb) {
    // ...
}


int main()
{
    describe("Box", [&](itFunc it) {
        it("is solid", [&]() {
            return true;
        });
        
        // How do I allow for two different `it` functions (different signatures)?
        //it("is needing to be implemented");
    });
    
    std::cout << "asdf" << std::endl;
    
    return 0;
}


