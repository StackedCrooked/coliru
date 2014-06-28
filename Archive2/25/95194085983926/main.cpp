#include <iostream>
#include <stdexcept>
#include <functional>

#define REQUIRE_SEMICOLON (void)0
#define APPLICATION_EDGE_TITLE(token, code) \
    try \
        code \
    catch(std::exception const &e) { \
        std::cout << token << " error: " << e.what() << std::endl; \
    } catch(...) { \
        std::cout << token << " unknown error" << std::endl; \
    } REQUIRE_SEMICOLON

#define APPLICATION_EDGE(code) APPLICATION_EDGE_TITLE("ENGINE_GENERIC_ERROR_TITLE", code)

struct Foo {};

int main()
{
    APPLICATION_EDGE({
        //throw std::runtime_error{ "poop" };
        throw Foo{};
    } catch (Foo &) {
        std::cout << "noap" << std::endl;
    });
    
    APPLICATION_EDGE_TITLE("SOME_ERROR", {
        throw std::runtime_error{ "poop" };
    });
    
	std::cout << "still alive" << std::endl;
}
