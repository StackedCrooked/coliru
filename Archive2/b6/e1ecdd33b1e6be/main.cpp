#include <iostream>

struct QNetworkAccessManager {
    void get() { std::cout << "It works\n"; }
};

class C {
public:
    void doIt() {
        manager->get();
    }

private:
    QNetworkAccessManager *manager;
};

int main() {
    C c;
    c.doIt();
}