#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <iterator>
namespace onhands
{

    struct Product
	{
		float price;
		explicit Product(float price) : price(price) {}
		// it is only allowed to add new context (modification of above is forbidden)
        
        friend std::ostream & operator<<(std::ostream &os, const Product& p)
        {
            os.precision(5);
            return os << p.price;
        }
        
        bool operator<(Product const& rhs) const
        {
            return price < rhs.price;
        }
    
	};
}
using namespace <onhands>

	//TODO: return x cheapest products, where x is function param (num)
	std::vector<Product> find_cheapest(std::vector<Product> const& v, unsigned num)
	{
        std::vector<Product> tempVector(v.begin(), v.end());
        //tempVector=v;
        //tempVector.insert(v.begin(), v.end());
		// Please pay attention to performance.
        nth_element(tempVector.begin(), tempVector.begin() + num, tempVector.end());
        
		return std::vector<Product>(tempVector.begin(),tempVector.end());
	} // namespace onhands

	int main2(int, char**)
	{
		std::vector<onhands::Product> products;
		for (int i = 1; i < 100; ++i)
		{
			products.push_back(onhands::Product(static_cast<float>(i)));
		}
		std::random_shuffle(products.begin(), products.end());
		std::vector<onhands::Product> cheapest = find_cheapest(products, 20);

		// Print output without using loop.
        //std::copy(cheapest.begin(), cheapest.begin()+20, std::ostream_iterator<double>(std::cout,", "));;

		return 0;
	}

