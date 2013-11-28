#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <sstream>

// store the products, a set is ideal because of the HINT:
std::unordered_set<unsigned> products;

/**
 * Insert to products if string arguments is a proper product
 */
void insert_if_product(std::string const& factor1, std::string const& factor2, std::string const& product) {
    auto p = std::stoul(product);
    if (std::stoul(factor1, nullptr, 10) * std::stoul(factor2, nullptr, 10) == p) {
        products.insert(p);
    }
}

/**
 * magnitudes needs to add up: I'm checking 
 * 9 digits total
 * m1 * m3 = m5
 * m1 * m4 = m4
 * m2 * m3 = m4
 * Is this all?
 * 
 * @param check this permutation
 */

void check_products(std::string const& perm)
{
    static std::string factor1, factor2, product;
    // all permutations are coming from perm, so no need to perm stuff here.
    factor1.assign(perm.begin()+0, perm.begin()+1);
    factor2.assign(perm.begin()+1, perm.begin()+4);
    product.assign(perm.begin()+4, perm.begin()+9);

    insert_if_product(factor1, factor2, product);

    factor1.assign(perm.begin()+0, perm.begin()+1);
    factor2.assign(perm.begin()+1, perm.begin()+5);
    product.assign(perm.begin()+5, perm.begin()+9);

    insert_if_product(factor1, factor2, product);

    factor1.assign(perm.begin()+0, perm.begin()+2);
    factor2.assign(perm.begin()+2, perm.begin()+5);
    product.assign(perm.begin()+5, perm.begin()+9);

    insert_if_product(factor1, factor2, product);
}

int main() {
    std::string s = "123456789";

    do {
        check_products(s);
    } while(std::next_permutation(std::begin(s), std::end(s)));

    std::cout << "Sum:" << std::accumulate(products.begin(), products.end(), 0u) << "\n";
}
