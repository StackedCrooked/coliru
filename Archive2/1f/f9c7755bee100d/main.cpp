#include <functional>
#include <iostream>
#include <vector>


template<typename T, typename... Args>
class Functions
{
    private:
        std::vector<std::function<T(Args...)>> vec;

    public:
        void operator += (std::function<T(Args...)> f)
        {
            vec.push_back(f);
        }

        void operator()(Args... args)
        {
            for (auto &f : vec)
            {
                f(std::forward<Args>(args)...);
            }
        }
};

template <typename T, typename... Args, typename...func_Ts>
Functions<T, Args...> make_Functions( func_Ts ... funcs) {
    Functions<T, Args...> ret;
    using magic=int[];
    magic{((ret+=std::forward<func_Ts>(funcs)),0)...,0};
    return ret;
}

int main()
{
    Functions<void> funcs;
    funcs += []{std::cout<<"Foo\n";};
    funcs += []{std::cout<<"Bar\n";};
    funcs();
    std::cout<<"\n";

    Functions<void, int> funcs2;
    funcs2 += [](int a){std::cout<<"Foo"<<a<<"\n";};
    funcs2 += [](int b){std::cout<<"Bar"<<b<<"\n";};
    funcs2(2);
    std::cout<<"\n";    
    
    Functions<void, int> funcs3 = make_Functions<void, int>(
            [](int a){std::cout<<"Foo"<<a<<"\n";},
            [](int b){std::cout<<"Bar"<<b<<"\n";}
        );
    funcs3(3);
    std::cout<<"\n";

}