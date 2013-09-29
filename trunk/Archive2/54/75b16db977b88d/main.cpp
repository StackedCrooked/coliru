#include <iostream>
#include <memory>


struct lol {
    int x;
    std::shared_ptr<lol> child;
    lol(int y): x(y) { std::cout << "Constructed " << x << '\n'; }
    lol(int y, std::shared_ptr<lol> stuff): x(y), child(std::move(stuff)) {}
    ~lol() { std::cout << "Destructed " << x << '\n'; }
    
    friend lol operator&&(const lol& lhs, const lol& rhs) {
        return lol(lhs.x, std::shared_ptr<lol>(new lol(rhs.x)));
    }
};

int main() {
    lol one(1);
    lol two(2);
    lol three = one && two;
}
    