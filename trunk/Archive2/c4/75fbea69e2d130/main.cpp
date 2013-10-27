#include <utility>
#include <iostream>

template<typename First, typename ... Rest>
void Output(First&& first, Rest&&... rest) {
    std::cout << std::forward<First>(first);
    int sink[]{(std::cout<<" "<<std::forward<Rest>(rest),0)... };
    (void)sink; // silence used variable" warning
    std::cout << std::endl;
}

int main() {
    Output("I","am","a","sentence");
    Output("Let's","try",1,"or",2,"digits");

    // Output();
}
