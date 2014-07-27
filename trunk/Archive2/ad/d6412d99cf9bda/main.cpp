struct Event{};
struct Receiver {
    void receive(const Event &) {   
    }
};

int main() {
    void (Receiver::*func)(const Event &) = &Receiver::receive;
}