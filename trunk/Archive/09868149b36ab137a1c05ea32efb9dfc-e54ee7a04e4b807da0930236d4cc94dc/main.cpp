#include "sales_data.h"


sales_data::sales_data(std::istream& is)
{
read(is, *this);
}

double sales_data::avg_price() const
{
if (units_sold)
    return = revenue/units_sold;
else
   return 0;
}


sales_data& sales_data::combine(const sales_data& rhs)
{
units_sold += rhs.units_sold;
revenue += rhs.revenue;
return *this;
}


sales_data add(const sales_data& lhs, const sales_data& rhs)
{
sales_data sum = lhs;
sum.combine(rhs);
return sum;
}


std::istream& read(std::istream& is, sales_data& item)
{
is>>item.bookNo>>item.units_sold>>price;
item.revenue = price * item.units_sold;
return is;
}

std::ostream& print(std::ostream& os, const sales_data& item);
{
os<<item.bookNo<<" "<<item.units_sold<<" "<<item.revenue<<" "<<item.avg_price();
return os;
}


