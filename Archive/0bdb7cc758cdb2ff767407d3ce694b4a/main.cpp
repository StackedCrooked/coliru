#include <functional>
#include <iostream>
#include <map>

void run_test()
{
    int e;
    e = system("ln -s test server && ./server");
    e = system("ln -s test client && ./client");    
    (void)e;
}

void run_server() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
void run_client() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

struct Function : std::function<void()>
{
    template<typename ...Args>
    Function(Args && ...args) : std::function<void()>(std::forward<Args>(args)...) {}

    Function() : std::function<void()>([]{ std::cerr << "Invalid program name." << std::endl; } ) {}
};

static std::map<std::string, Function> startup = {
    { "test"  , &run_test   },
    { "server", &run_server },
    { "client", &run_client }
};

int main(int /*argc*/, char ** argv)
{
    auto basename = [](std::string s) { return s.substr(s.rfind('/') + 1); };
    auto program_name = basename(argv[0]);
    startup[program_name]();
}
