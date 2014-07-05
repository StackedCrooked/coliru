#include <iostream>     // cout
#include <vector>       // vector

class Product
{
    public:
    static int ID;
    static int Copies;
    int pid;
    Product() {
        pid = ++ID;
        std::cout << "Product Constructed : " << pid << "\n";
    }
    Product(const Product& p) {
        pid = ++ID;
        Copies++;
        std::cout << "Product Copied : " << p.pid << "->" << pid << "\n";
    }
};

int Product::ID = 0;
int Product::Copies = 0;
int checkPoint = 0;

int main() 
{
    auto write = [](const std::string& s){std::cout<<s<<"\n";};
    
    auto p1 = Product();
    auto p2 = new Product();
    
    auto ctr = std::vector<Product>();
    
    write("pushing value");
    ctr.push_back(p1);
    write("pushing value of pointer");
    ctr.push_back(*p2);
    
    write("pushing something aberrant");
    ctr.push_back(*(new Product()));
    
    write("pushing in-initialized object");
    ctr.push_back(Product());
    
    for(auto item : ctr)
        std::cout << "CTR ID" << item.pid << "\n";
}

    
