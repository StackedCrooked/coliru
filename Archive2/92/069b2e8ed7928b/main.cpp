#include <string>
#include <iostream>

template<typename First, typename ... Strings>
void Output(First arg, const Strings&... rest) {
    std::cout << arg;
    int sink[]{(std::cout<<" "<<rest,0)... };
    (void)sink;
    std::cout << std::endl;
}

int main() {
    Output("I","am","a","sentence");
    Output("Let's","try",1,"or",2,"digits");
    // Output(); //<- I do not want this to compile, but it does.

    return 0;
}
