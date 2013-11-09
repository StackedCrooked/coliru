#include <string>
#include <exception>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


struct Product
{
    int id;
    std::string name;
};


struct TargetNotFound : public std::exception
{
    TargetNotFound(const std::string &target) : target(target) {}

    std::string getTarget() const
    {
        return target;
    }

private:
    const std::string target;
};


int getProductID(const std::vector<Product> &p, const std::string &target)
{
    auto i = std::find_if(p.begin(), p.end(), [&](const Product &x)
    {
        return x.name==target;
    });

    if (i == p.end())
        throw TargetNotFound(target);
    else
        return i->id;
}


int main()
{

    std::vector<Product> products
    {
        {4, "computers"},
        {5, "flash drive"},
        {8, "mouse"},
        {10, "printer"},
        {13, "camera"},
    };

    try
    {
        cout<< getProductID(products, "mouse")<<endl;
        cout<< getProductID(products, "camera")<<endl;
        cout<<getProductID(products, "laptop")<<endl;
    }
    catch(const TargetNotFound &ex)
    {
        cout<<"Error: "<< ex.getTarget() << " product not found."<< endl;
        cout<<"End of program."<<endl;
    }
}
