#include <type_traits>

class Client {};
class Derived : public Client {};
class NonDerived {};

template <typename CLIENT>
class Server
{
    static_assert(std::is_base_of<Client, CLIENT>::value, "Template type must derive from Client");
};

int main() {
    Server<Client> a;
    Server<Derived> b;
    Server<NonDerived> c; //error: static assertion failed: Template type must derive from Client
}