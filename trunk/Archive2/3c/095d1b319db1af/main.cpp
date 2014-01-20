#include <memory>
#include <vector>

struct Product{
};

struct Book : public Product{
};

struct Magazine: public Product{
};

int main(){
    std::vector<std::shared_ptr<Product> > products;
    //C++11
    products.emplace_back(new Book());
    products.emplace_back(new Magazine());

    //C++03TR1
    // we don't have emplace_back here so we need to 
    // construct both the shared_ptr and the book
    products.push_back(std::shared_ptr<Product>(new Book()));
}