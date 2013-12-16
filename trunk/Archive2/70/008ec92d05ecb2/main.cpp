#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

struct Product {
    std::unique_ptr<std::string> description;
};

struct Basket {
    // this line is OK, just moves it
    std::vector<Product> ps;
    // Doesn't compile with this line uncommented ! Can't move map ?
    // std::unordered_map<std::string, std::vector<Product>> repo;
};


int main(int argc, const char *argv[]) {

    std::vector<Basket> baskets;
    Basket b1;
    baskets.push_back(std::move(b1));

    return 0;
}