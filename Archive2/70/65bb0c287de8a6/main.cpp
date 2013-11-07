// kapitel016/smartpointer04.cpp
#include <iostream>
#include <string>
#include <memory>

class Data {
    std::string label;
public:
    Data(std::string l):label(l) {
        std::cout << l << " erzeugt\n";
    }
    ~Data() { std::cout << label << " zerstört\n";}
    void printLabel(){std::cout << "Data: " << label
        << std::endl;}
    void setLabel(const std::string& s) {label=s;}
};

class DataPool {
    std::shared_ptr<Data> dPtr;
public:
    void setData(std::shared_ptr<Data> ptr) {
        std::cout << "Neue Daten im Datenpool\n";
        dPtr = ptr;
    }
};

int main() {
    std::cout << "\n\nProgrammanfang\n";
    {
        std::shared_ptr<Data> d01(new Data("Buchhaltung1"));
        std::shared_ptr<Data> d02 = std::make_shared<Data>("Buchhaltung2");
        auto d03 = std::make_shared<Data>("Buchhaltung3");
        Data mydat("Buchhaltung4");
        auto d04 = std::make_shared<Data>(mydat);
    }
    std::cout << "Programmende\n\n";
}

