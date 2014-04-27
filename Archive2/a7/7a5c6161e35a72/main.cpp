
    #include <iostream>

    struct Fun {
        void operator()() & {
            std::cout << "L-Value\n";
        }
        void operator()() && {
            std::cout << "R-Value\n";
        }        

    };

    template <class Function>
    void apply(Function&& function)
    {
        function();
    }
 
    template <class Function>
    void apply_forward(Function&& function)
    {
        std::forward<Function>(function)();
    }

    int main () {
        apply(Fun{}); // Prints "L-Value\n"
        apply_forward(Fun{}); // Prints "R-Value\n"
    }