#include <iostream>
#include <string>

template<typename>
void print()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

template<typename Command>
void Register()
{
    print<Command>();
    print<decltype(&Command::execute)>();
}

std::map< std::string, std::function<std::string(std::string)> > functions;





template<typename>
struct Signature;


template<typename R, typename ...A>
struct Signature<R(*)(A...)>
{
    using Res = R;
    using Arg = std::tuple<A...>;
};


void send(const std::string & ser)
{
}


template<typename C, typename ...Args>
void send(Args && ...args)
{
    using Sig = Signature<&C::execute>;
    using Arg = Sig::Arg;
    using Res = Sig::Res;
    using Cmd = std::string;
    send(serialize(std::pair<std::string, Arguments>(C::Name, Arguments(std::forward<Args>(args)...))));
}


template<T>
struct Registrator
{
    Registrator()
    {
        using Sig = Signature<&T::execute>;
        functions.insert(std::make_pair(Demangle(T), [](const std::string & msg) -> std::string {
            Sig::Ret && ret = T::execute(unpack(deserialize<Sig::Arg>(msg))...);
            return serialize(ret);
        });
    }
};


struct : Registrator<"Increment">
{
    static unsigned execute(unsigned n) { return n + 1; }
};
Registrator<Increment> gRegister;

int main()
{
    Register<Increment>();
    
    using IncSig = Signature<decltype(&Increment::execute)>;
    IncSig::ResultType
}