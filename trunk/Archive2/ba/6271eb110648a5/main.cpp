#include <iostream>

#include <map>
#include <vector>

std::map< std::string, void*> functions;

template<typename Ret, typename... Args>
    void Register(Ret(*function)(Args...)) {
        void* v = (void*)function;
        functions.insert(std::pair<std::string, void*>("A", v));
    }

int main()
{
    Register(&main);
}
