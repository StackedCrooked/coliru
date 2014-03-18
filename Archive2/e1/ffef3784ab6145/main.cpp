#include <type_traits>

class Client {};
class Derived : public Client {};
class NonDerived {};

template<class T, class Enable = void>
class Server;

template <typename CLIENT>
class Server<CLIENT, typename std::enable_if<std::is_base_of<Client, CLIENT>::value>::type> {};

int main(int argc, char* argv[]) {
    Server<Derived> x;
}