#include <fstream>
#include <vector>
#include <iostream>

struct Product { char name[200]; int code; double price; };

void fileWriteBin( const char* file_name, const std::vector<Product>& prod )
{
    std::ofstream file( file_name, std::ios::binary ) ;
    
    // note: since Product is a pod, its first member (name) must be at an offset of zero.
    for( const Product& p : prod ) file.write( p.name, sizeof(p) ) ;

}

std::vector<Product> readDataBinary( const char* file_name )
{
    std::vector<Product> prod ;
    std::ifstream file( file_name, std::ios::binary ) ;

    Product temp ;
    while( file.read( temp.name, sizeof(temp) ) ) // canonical; for every Product read from the file
        prod.push_back(temp) ; // add it to the vector

    return prod ;
}

int main()
{
    const char* const file_name = "products.bin" ;

    {
        std::vector<Product> prod
        {
            Product{ "Honey", 1, 12.34 },
            Product{ "Coffee", 2, 56.78 },
            Product{ "Claret", 3, 90.12 }
        };

        fileWriteBin( file_name, prod ) ;
    }

    {
        std::vector<Product> prod = readDataBinary(file_name) ;
        for( const Product& p : prod )
            std::cout << p.name << ' ' << p.code << ' ' << p.price << '\n' ;
    }
}
