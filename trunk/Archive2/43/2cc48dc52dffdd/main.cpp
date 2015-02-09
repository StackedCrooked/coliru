#include <boost/signals2.hpp>
#include <iostream>

class Listener {
public:
    virtual ~Listener() = default;
    virtual void OnUpdate() = 0;
};

class View : public Listener
{
public:
    View() = default;
    ~View() = default;
    virtual void OnUpdate() override {
        std::cout << "Updating in View\n";
    }
};

class Controller
{
    boost::signals2::signal<void ()> sig;
public:
    Controller() {
    }

    void subscribe(Listener& listener) {
        // Signal with no arguments and a void return value
        sig.connect(boost::bind(&Listener::OnUpdate, &listener));
    }

    void DoWork() const {
        // Call all of the slots
        sig();
    }

    void Update();
};

int main() {
    Controller c;

    View l1, l2;

    c.subscribe(l1);

    std::cout << "One subscribed:\n";
    c.DoWork();

    c.subscribe(l2);

    std::cout << "\nBoth subscribed:\n";
    c.DoWork();
}
