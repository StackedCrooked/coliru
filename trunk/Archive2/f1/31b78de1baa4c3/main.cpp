#include <iostream>
#include <string>

class Book {
    std::string name;
    int fee;
    int noPeople;
    int income;

public:
    Book(std::string name, int fee, int noPeople) :
        name(std::move(name)),
        fee(fee),
        noPeople(noPeople)
    {
    }

    void calIncome() {
        income = fee * noPeople;
    }

    void viewIncome() {
        calIncome();
        std:: cout << income << name;
    }
};

int main() {
    Book b1 ("DISE", 20000, 30);
    b1.viewIncome();
}