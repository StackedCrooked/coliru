#include <iostream>
#include <string>

using namespace std;

class Sales_data {
    
    friend Sales_data add(const Sales_data&, const Sales_data&);
    friend ostream &print(ostream&, const Sales_data&);
    friend istream &read(istream&, Sales_data&);

public:
    Sales_data() { };
    Sales_data(const string &s): bookNo(s) { }
    Sales_data(const string &s, unsigned n, double p): bookNo(s), unitsSold(n), revenue(p * n) { }
    Sales_data(istream &);
    
    string isbn() const { return bookNo; }
	Sales_data& combine(const Sales_data&);
    
private:
	double avg_price() const { return unitsSold ? revenue / unitsSold : 0; }
	string bookNo;
	unsigned unitsSold = 0;
	double revenue = 0.0;
};

Sales_data add(const Sales_data&, const Sales_data&);
ostream &print(ostream&, const Sales_data&);
istream &read(istream&, Sales_data&);

Sales_data& Sales_data::combine(const Sales_data &salesData) {
    unitsSold += salesData.unitsSold;
    revenue += salesData.revenue;
    return *this;
}

Sales_data::Sales_data(istream &is) {
    read(is, *this);    
}

istream &read(istream &is, Sales_data &item) {
    double price = 0;
    is >> item.bookNo >> item.unitsSold >> price;
    item.revenue = price * item.unitsSold;
    return is;
}

ostream &print(ostream &os, const Sales_data &item) {
    os << item.isbn() << " " << item.unitsSold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}

Sales_data add(const Sales_data &s1, const Sales_data &s2) {
    Sales_data sum = s1;
    sum.combine(s2);
    return sum;
}

int main() {
    Sales_data total;
    Sales_data trans;
    
    
}