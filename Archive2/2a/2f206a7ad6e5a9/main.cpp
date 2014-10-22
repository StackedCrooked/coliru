#include <utility>
#include <iostream>

template<class Type, class... Args>
Type* make_suicidal(Args&&... args) {
    return new Type(std::forward<Args>(args)...);
}

class PhoneCall {
private:
    PhoneCall() = default;
public:
    PhoneCall(PhoneCall&&) = default;
    PhoneCall(PhoneCall const&) = default;
    PhoneCall& operator=(PhoneCall&&) = default;
    PhoneCall& operator=(PhoneCall const&) = default;
    ~PhoneCall() { delete this; }
    
    void yolo() { std::cout << "#yolo"; }
    
    friend PhoneCall* make_suicidal<PhoneCall>();
};

int main() {
    auto* call = make_suicidal<PhoneCall>();
    call->yolo();
}