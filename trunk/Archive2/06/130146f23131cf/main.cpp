#include <boost/signals2.hpp>
#include <iostream>

struct View {
    void OnUpdate() { std::cout << "Updating in View\n"; }
};

class Controller {
    using UpdateHandler = boost::signals2::signal<void()>;
    UpdateHandler sig;

  public:
    Controller() {}

    void subscribe(UpdateHandler::slot_type handler) { sig.connect(handler); }
    void DoWork() const { sig(); }
    void Update();
};

int main() {
    Controller c;

    View l1;
    c.subscribe(std::bind(&View::OnUpdate, &l1));
    c.subscribe([] { std::cout << "Or we can attach a random action\n"; });

    c.DoWork();
}
