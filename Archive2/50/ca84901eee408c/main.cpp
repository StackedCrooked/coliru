#include <vector>
#include <string>
#include <iostream>

struct Money{
    Money(double amount_) : amount(amount_) {}
    Money() : Money(0.) {};
    double amount;
};

struct Book{
    Book(const std::string name_) : name(name_) {}
    bool operator==(const Book& rhs) const {
        return name == rhs.name;
    }
    std::string name;
};

struct Receipt{
    Receipt() : money(), books() {}
    Money money;
    struct BookInfo{
        BookInfo(const Book& book_, bool isPlus) : book(book_), plus(isPlus) {}
        const Book book;
        const bool plus;
    };
    std::vector<BookInfo> books;
    double Amount(const Book& book) const {
        for(const auto& b : books){
            if(book == b.book){
                return b.plus?money.amount:-(money.amount);
            }
        }
        return 0.;
    }
};

template <typename Container>
double Balance(const Book& book, const Container& c){
    double res = 0.;
    for(const auto& elem : c){
        res += elem.Amount(book);
    }
    return res;
}

template <typename Container>
double OffBudgets(const std::vector<Book>& accounts, const std::vector<Book>& budgets, const Container& c){
    double res = 0.;
    for(const auto& account : accounts){
        res += Balance(account, c);
    }
    for(const auto& budget : budgets){
        res -= Balance(budget, c);
    }
    return res;
}

int main() {
    using namespace std;
    
    std::vector<Book> accounts;
    accounts.push_back( Book{"UC"} );
    accounts.push_back( Book{"GE"} );
    accounts.push_back( Book{"CB"} );
    accounts.push_back( Book{"CC"} );

    std::vector<Book> budgets;
    budgets.push_back( Book{"Ent"} );
    budgets.push_back( Book{"Gad"} );
    budgets.push_back( Book{"Ves"} );
    budgets.push_back( Book{"Sav"} );
    
    std::vector<Receipt> money;
    Receipt tmp;
    
    tmp.money.amount = 400;
    tmp.books.push_back( Receipt::BookInfo{Book{"UC"}, true } );
    money.push_back(tmp);
    tmp.books.clear();
    
    tmp.money.amount = 1500;
    tmp.books.push_back( Receipt::BookInfo{Book{"CB"}, true } );
    money.push_back(tmp);
    tmp.books.clear();
    
    tmp.money.amount = 1440;
    tmp.books.push_back( Receipt::BookInfo{Book{"CC"}, false } );
    money.push_back(tmp);
    tmp.books.clear();
    
    tmp.money.amount = 1440;
    tmp.books.push_back( Receipt::BookInfo{Book{"CC"}, true } );
    tmp.books.push_back( Receipt::BookInfo{Book{"CB"}, false } );
    money.push_back(tmp);
    tmp.books.clear();
    
    tmp.money.amount = 250;
    tmp.books.push_back( Receipt::BookInfo{Book{"Ent"}, true } );
    money.push_back(tmp);
    tmp.books.clear();
    
    tmp.money.amount = 2.40;
    tmp.books.push_back( Receipt::BookInfo{Book{"UC"}, false } );
    money.push_back(tmp);
    tmp.books.clear();
    
    tmp.money.amount = 25.5;
    tmp.books.push_back( Receipt::BookInfo{Book{"UC"}, false } );
    tmp.books.push_back( Receipt::BookInfo{Book{"Ent"}, false } );
    money.push_back(tmp);
    tmp.books.clear();
    
    cout << "UC: " << Balance(Book{"UC"}, money) << endl;
    cout << "CB: " << Balance(Book{"CB"}, money) << endl;
    cout << "CC: " << Balance(Book{"CC"}, money) << endl;
    cout << "Ent: " << Balance(Book{"Ent"}, money) << endl;
    
    cout << "off budgets: " << OffBudgets(accounts, budgets, money) << endl;
}
