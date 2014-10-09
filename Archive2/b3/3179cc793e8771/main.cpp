#include <iostream>
#include <string>
#include <fstream>

class Sales_data
{
    friend std::istream &read(std::istream &is, Sales_data &item);
    friend std::ostream &print(std::ofstream &os, const Sales_data &item);
    friend std::istream& operator >>(std::istream & in, Sales_data &s);
    friend std::ostream& operator<<(std::ostream& out, const Sales_data& s);

public:
    Sales_data() : Sales_data("8-888-88888-8", 0, 0) { }
    Sales_data(std::istream &is);
    Sales_data(const std::string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p*n) { }
    Sales_data(const std::string &s) : Sales_data(s, 0, 0.0) { }


    Sales_data& operator+=(const Sales_data&);
    Sales_data& combine(const Sales_data& rhs);
    std::string isbn() const;
    double avg_price() const;

private:
    std::string bookNo;
    unsigned units_sold;
    double price;
    double revenue;
};

Sales_data::Sales_data(std::istream &is)
{
    is >> bookNo >> units_sold >> price;
    revenue = units_sold * price;
}

Sales_data& Sales_data::operator+=(const Sales_data& rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

Sales_data& Sales_data::combine(const Sales_data& rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

std::string Sales_data::isbn() const
{
    return bookNo;
}

inline double Sales_data::avg_price() const
{
    if (units_sold)
        return revenue / units_sold;
    else
        return 0;
}

// Nonmember Class-related functions

Sales_data add(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}

std::istream &read(std::istream &is, Sales_data &item)
{
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

std::ostream &print(std::ofstream &os, const Sales_data &item)
{
    os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();
    return os;
}

std::istream& operator >>(std::istream & in, Sales_data &s)
{
    double price;
    in >> s.bookNo >> s.units_sold >> price;
    if (in)
        s.revenue = s.units_sold * price;
    else
        s = Sales_data();
    return in;
}

std::ostream& operator<<(std::ostream& out, const Sales_data& s)
{
    out << s.bookNo << " " << s.units_sold << " "
        << s.revenue << " " << s.avg_price();
    return out;
}

int main()
{
    const char* filename = "books.txt";
    const char* outfile = "output.txt";
    std::ifstream namefile(filename);
    std::ofstream output(outfile);
    //std::string line;

    Sales_data total;
    Sales_data trans;
    namefile >> total;

    while (namefile >> trans)
    {
        if (total.isbn() == trans.isbn())
            total = add(total, trans);
        else
        {       
            print(output, total) << std::endl;
            total = trans;
        }
    }
}

