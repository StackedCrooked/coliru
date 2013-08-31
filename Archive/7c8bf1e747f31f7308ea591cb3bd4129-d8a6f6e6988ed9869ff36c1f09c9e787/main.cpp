#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>

using HashTable = std::vector<int>;

std::ostream& operator<<(std::ostream& os, const HashTable & table)
{
    for (const auto & n : table) os << std::setw(5) << n << " ";
    return os;
}

void hash(int in, int & out)
{
    out = in % 10;
}

template<typename T>
T hash(const T & t)
{
    T result;
    hash(t, result);
    return result;
}


void insert(HashTable & table, int n)
{
    auto index = hash(n);
    while (table[index])
    {
        const int len = table.size();
        if (++index == len) index = 0;
        if (index == hash(n)) throw std::runtime_error("HashTable is full!");
    }
    table[index] = n;
}

int main()
{
    
    HashTable table(10);
    for (int i = 1; i != 100; ++i)
    {
        auto n = rand() % 100;
        std::cout << "n: " << n << "    ";
        insert(table, n);
        std::cout << table << std::endl;
    }
}