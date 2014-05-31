#include <iostream>

// The visitor class. Clients can register methods here.
class Visitor {
  public:
    template <class T>
    using method_t = void (T::*)();

    // Register a new method of a client.
    template <class T>
    void subscribe(method_t<T> method, T* object) {
        std::cout << "Registered method: " << method
                  << " of object: " << object << "\n";
        std::cout << "Calling...\n";
        (object->*method)();
        std::cout << "Called.\n";
    }

    // unsubscribe all methods of a given client.
    template <class T>
    void unsubscribe(T* object) {
        std::cout << "Unregistered object: " << object << "\n";
    }
};

// A simple client. Has to subscribe and unsubscribe manually.
class Client {
  public:
    Client(Visitor &visitor) : visitor_(visitor) {
        visitor_.subscribe(&Client::method, this);
    }
    ~Client() {
        visitor_.unsubscribe(this);
    }
    void method() {
        std::cout << "Method says hi!\n";
    }

  private:
    Visitor &visitor_;
};

// CRTP registration class.
// Will automatically subscribe and unsubscribe its base class.
template <class Derived>
class Registration {
  public:
    Registration(Visitor &visitor, Visitor::method_t<Derived> method)
        : visitor_(visitor) {
        visitor_.subscribe(method, static_cast<Derived *>(this));
    }

    virtual ~Registration() {
        visitor_.unsubscribe(static_cast<Derived *>(this));
    }

  private:
    Visitor &visitor_;
};

// Another client this time using the registration class.
// Has to inherit publically, otherwise the pointer cast will fail.
class AnotherClient : public Registration<AnotherClient> {
  public:
    AnotherClient(Visitor &visitor)
        : Registration<AnotherClient>(visitor, &AnotherClient::method) {}

    void method() {
        std::cout << "Another method says hi!\n";
    }
};

int main() {
    Visitor visitor;

    {
        std::cout << " -- Client\n";
        Client client(visitor);
    }
    {
        std::cout << "\n -- AnotherClient\n";
        AnotherClient client2(visitor);
    }
}
