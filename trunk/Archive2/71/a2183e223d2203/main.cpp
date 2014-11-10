#include <initializer_list>
#include <iostream>
using namespace std;

struct Book;
struct Album;
struct Game;
struct Magazine;

struct ItemVisitor {
    virtual void visit(const Book&) = 0;
    virtual void visit(const Album&) = 0;
    virtual void visit(const Magazine&) = 0;
    virtual void visit(const Game&) = 0;
};

struct Item {
    virtual void accept(ItemVisitor& visitor) = 0;
};

template <typename D, typename PV>
struct Accepter {
    virtual void accept(PV& visitor) {
        visitor.visit(*dynamic_cast<D>(this));
    }
};

struct Book : public Item, public Accepter<Book, ItemVisitor> {
};

struct Album : public Item, public Accepter<Album, ItemVisitor> {
};

struct Magazine : public Item, public Accepter<Magazine, ItemVisitor> {
};

struct Game : public Item, public Accepter<Game, ItemVisitor> {
};

struct PriceVisitor : public ItemVisitor {
    PriceVisitor() {}
    virtual void visit(const Book& book) {
        total_ += 10.0f;
    }
    virtual void visit(const Album&) {
        total_ += 25.0f;
    }
    virtual void visit(const Magazine&) {
        total_ += 8.0f;
    }
    virtual void visit(const Game&) {
        total_ += 120.0f;
    }
    float totalPrice() {
        return total_;
    }
    
    float total_ = 0.0f;
};

struct PrintVisitor : public ItemVisitor {
    PrintVisitor() {}
    ~PrintVisitor() { cout << endl; }
    virtual void visit(const Book& book) {
        cout << "Book, ";
    }
    virtual void visit(const Album&) {
        cout << "Album, ";
    }
    virtual void visit(const Magazine&) {
        cout << "Magazine, ";
    }
    virtual void visit(const Game&) {
        cout << "Game, ";
    }
    
    float total_ = 0.0f;
};

float price(const initializer_list<Item*> items) {
    PriceVisitor priceVisitor;
    for (Item* i : items) {
        i->accept(priceVisitor);
    }
    return priceVisitor.totalPrice();
}

void print_items(const initializer_list<Item*> items) {
    PrintVisitor printVisitor;
    for (Item* i : items) {
        i->accept(printVisitor);
    }
}

int main() {
    auto items = initializer_list<Item*>{new Book(), new Album(), new Magazine(), new Game()};
    cout << "Price: " << price(items) << endl;
    cout << "Print items: "; print_items(items);
}
