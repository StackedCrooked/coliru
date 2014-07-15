#include <iostream>

using namespace std;

class Sales_data
{
    friend istream &read(istream &, Sales_data &);
    public:
        Sales_data(const string &s, unsigned n, double p): bookNo(s), units_sold(n),    revenue(p*n) { }
        explicit Sales_data(const string &s = ""): Sales_data(s, 0, 0) { }
        Sales_data(istream &is): Sales_data() {read(is, *this);}
    private:
        string bookNo;
        unsigned units_sold = 0;
        double revenue = 0.0;
};

istream &read(istream &is, Sales_data &item)
{
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}
