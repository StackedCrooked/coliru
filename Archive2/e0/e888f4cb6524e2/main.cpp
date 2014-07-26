#include <iostream>
#include <string>
class Quote
{
public:
Quote() { std::cout << "default constructing Quote\n"; }
Quote(const std::string &b, double p) :
bookNo(b), price(p) {
std::cout << "Quote : constructor taking 2 parameters\n";
}
private:
std::string bookNo;


protected:
double price = 10.0;
};


//然后是disc_quote类
class Disc_quote : public Quote
{
public:
Disc_quote() { std::cout << "default constructing Disc_quote\n"; }


Disc_quote(const std::string& b, double p, std::size_t q, double d) :
Quote(b, p), quantity(q), discount(d)
{
std::cout << "Disc_quote : constructor taking 4 parameters.\n";
}
protected:
std::size_t quantity = 3;
double discount = 0.0;
};


//最后是bulk_quote类


class Bulk_quote : public Disc_quote
{
public:
Bulk_quote() { std::cout << "default constructing Bulk_quote\n"; }
using Disc_quote::Disc_quote;
};


//还有main函数
int main()
{
Bulk_quote bq("sss", 20.0, 2, 0.3);
return 0;
}