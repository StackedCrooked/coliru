#include <iostream>
#include <stdexcept>
#include <functional>

void applicationEdge(std::string const &token, std::function<void ()> const &f) {
    try
    { f(); }
    catch(std::exception const &e)
    { std::cout << token << " error: " << e.what() << std::endl; }
    catch(...)
    { std::cout << token << " unknown error" << std::endl; }
}
#define APPLICATION_EDGE(code) applicationEdge("ENGINE_GENERIC_ERROR_TITLE", [&]code)
#define APPLICATION_EDGE_TITLE(token, code) applicationEdge(token, [&]code)

int main()
{
	APPLICATION_EDGE({
        throw std::runtime_error{ "poop" };
    });
    
    APPLICATION_EDGE_TITLE("SOME_ERROR", {
        throw std::runtime_error{ "poop" };
    });
    
	std::cout << "still alive" << std::endl;
}