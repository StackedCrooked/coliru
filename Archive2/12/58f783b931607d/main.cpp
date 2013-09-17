// carstats.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <fstream>
using namespace std;

enum CarType
{
    Ford,
    Chevy,
    Honda,
    Toyota
};

struct Stats
{
    unsigned units_sold;
    double total_turnover;
    Stats() : units_sold(0), total_turnover(0.0) {}
};

typedef map<CarType, Stats> Statistics;

ostream& operator<<(ostream& os, CarType ct) {
    switch(ct) {
        case Ford:    return os << "Ford";
        case Chevy:   return os << "Chevy";
        case Honda:   return os << "Honda";
        case Toyota:  return os << "Toyota";
    }
    return os << "Unknown";
}

struct CarCustomer
{
    string firstName;
    string lastName;
    double price;
    CarType carType;
};

Statistics calcCarStats(vector<CarCustomer> const& arrCustomers)
{
    Statistics stats;
    for (auto& customer : arrCustomers)
    {
        auto& entry = stats[customer.carType];

        entry.units_sold     += 1;
        entry.total_turnover += customer.price;
    }

    return stats;
} 

void displayCarTypeCounts(Statistics const& stats)
{
    for (auto& entry: stats)
        cout << (CarType)entry.first << " " << entry.second.units_sold << " " << entry.second.total_turnover << endl;
}

int main()
{
    vector<CarCustomer> arrCustomers;

    CarCustomer current;
    int carTypeInt;
    while (cin >> current.firstName >> current.lastName >> current.price >> carTypeInt)
    {
        current.carType = (CarType)carTypeInt;
        arrCustomers.push_back(current);
    }

    auto stats = calcCarStats(arrCustomers);
    displayCarTypeCounts(stats);
}
