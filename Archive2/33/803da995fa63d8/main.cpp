#ifndef SALESITEM_H
// we're here only if SALESITEM_H has not yet been defined 
#define SALESITEM_H

//#include "Version_test.h" 

// Definition of Sales_item class and related functions goes here
#include <iostream>
#include <string>

class Sales_item {
    // these declarations are explained section 7.2.1, p. 270 
	// and in chapter 14, pages 557, 558, 561
	friend std::istream& operator>>(std::istream&, Sales_item&);
	friend std::ostream& operator<<(std::ostream&, const Sales_item&);
	friend bool operator<(const Sales_item&, const Sales_item&);
	friend bool
		operator==(const Sales_item&, const Sales_item&);
public:
	// constructors are explained in section 7.1.4, pages 262 - 265
	// default constructor needed to initialize members of built-in type
#if defined(IN_CLASS_INITS) && defined(DEFAULT_FCNS)
	Sales_item() = default;
#else
	Sales_item() : units_sold(0), revenue(0.0) { }
#endif
	Sales_item(const std::string &book) :
		bookNo(book), units_sold(0), revenue(0.0) { }
	Sales_item(std::istream &is) { is >> *this; }
public:
	// operations on Sales_item objects
	// member binary operator: left-hand operand bound to implicit this pointer
	Sales_item& operator+=(const Sales_item&);

	// operations on Sales_item objects
	std::string isbn() const { return bookNo; }
	double avg_price() const;
	// private members as before
private:
	std::string bookNo;      // implicitly initialized to the empty string
#ifdef IN_CLASS_INITS
	unsigned units_sold = 0; // explicitly initialized
	double revenue = 0.0;
#else
	unsigned units_sold;
	double revenue;
#endif
};

// used in chapter 10
inline
bool compareIsbn(const Sales_item &lhs, const Sales_item &rhs)
{
	return lhs.isbn() == rhs.isbn();
}

// nonmember binary operator: must declare a parameter for each operand
Sales_item operator+(const Sales_item&, const Sales_item&);

inline bool
operator==(const Sales_item &lhs, const Sales_item &rhs)
{
	// must be made a friend of Sales_item
	return lhs.units_sold == rhs.units_sold &&
		lhs.revenue == rhs.revenue &&
		lhs.isbn() == rhs.isbn();
}

inline bool
operator!=(const Sales_item &lhs, const Sales_item &rhs)
{
	return !(lhs == rhs); // != defined in terms of operator==
}

// assumes that both objects refer to the same ISBN
Sales_item& Sales_item::operator+=(const Sales_item& rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}

// assumes that both objects refer to the same ISBN
Sales_item
operator+(const Sales_item& lhs, const Sales_item& rhs)
{
	Sales_item ret(lhs);  // copy (|lhs|) into a local object that we'll return
	ret += rhs;           // add in the contents of (|rhs|) 
	return ret;           // return (|ret|) by value
}

std::istream&
operator>>(std::istream& in, Sales_item& s)
{
	double price;
	in >> s.bookNo >> s.units_sold >> price;
	// check that the inputs succeeded
	if (in)
		s.revenue = s.units_sold * price;
	else
		s = Sales_item();  // input failed: reset object to default state
	return in;
}

std::ostream&
operator<<(std::ostream& out, const Sales_item& s)
{
	out << s.isbn() << " " << s.units_sold << " "
		<< s.revenue << " " << s.avg_price();
	return out;
}

double Sales_item::avg_price() const
{
	if (units_sold)
		return revenue / units_sold;
	else
		return 0;
}
#endif

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

struct Sales_data
{
	std::string bookNo;
	unsigned units_sold;
	double revenue;
};

#include <sstream>
int main()
{
    struct cin_wrapper {
        cin_wrapper(const char* data) : input(data), old_buf(std::cin.rdbuf()) {
            std::cin.rdbuf(input.rdbuf());
        }
        ~cin_wrapper() {
            std::cin.rdbuf(old_buf);
        }
        std::istringstream input;
        std::streambuf* const old_buf;
    } cin_wrapper{R"(124578 8 6.99
124578 7 5.50
124578 5 6.00
524568 4 10.95
783625 4 19.99
783625 7 25.00)"};

	Sales_item total;
	
	if (std::cin >> total)
	{
		Sales_item trans;
		while (std::cin >> trans)
		{
			if (total.isbn() == trans.isbn())
				total += trans;
			else
			{
				std::cout << total << std::endl;
				total = trans;
			}
		}
		std::cout << total << std::endl;
	}
	else
	{
		std::cerr << "No data?" << std::endl;
		return -1;
	}


	int x = 0;
	std::cin >> x;

	return 0;
}
