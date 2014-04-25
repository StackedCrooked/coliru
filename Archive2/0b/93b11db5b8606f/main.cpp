#include <iostream>
#include <fstream>
#include <iomanip>

const int DESC_SIZE = 37;

struct Item
{
    int itemId;
    char description[DESC_SIZE];
    double cost, price;
    
    friend std::istream& operator>>(std::istream& in, Item& Inventory) 
    {
        in >> Inventory.itemId >> Inventory.cost >> Inventory.price;
        in.getline(Inventory.description, DESC_SIZE);
        return in;
    }
    
    friend std::ostream& operator<<(std::ostream& out, const Item& Inventory) 
    {
        out << "      " << Inventory.itemId;
        out << "     " << std::setw(5) << Inventory.cost;
        out << "       " << std::setw(5) << Inventory.price;
        out << " " << Inventory.description << '\n';
        return out;
    }
};

int processFile(const char* saifFile, const char* raofFile)
{
    std::ofstream outFile;
    std::ifstream inFile(saifFile);
    
    Item Inventory;
    while (inFile >> Inventory)
        std::cout << Inventory;

    return 0;
}