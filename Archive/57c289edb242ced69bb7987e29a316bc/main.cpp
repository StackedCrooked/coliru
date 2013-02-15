#include <functional>
#include <iostream>
#include <map>

void run_server() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
void run_client() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

struct Function : std::function<void()>
{
    template<typename ...Args>
    Function(Args && ...args) : std::function<void()>(std::forward<Args>(args)...) {}

    Function() : std::function<void()>([]{ std::cerr << "Invalid program name." << std::endl; } ) {}
};

static std::map<std::string, Function> startup = {
    { "server", &run_server },
    { "server", &run_client }
};

int main(int argc, char ** argv)
{
    auto basename = [](std::string s) { return s.substr(s.rfind('/') + 1); };
    auto program_name = basename(argv[0]);
    std::cout << "Program name: " << program_name << std::endl;
    startup[program_name]();
}
