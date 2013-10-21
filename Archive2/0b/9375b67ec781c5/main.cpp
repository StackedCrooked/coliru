#include <iostream>
#include <string>
using namespace std;   

#define MAX_CUSTOMERS 10
#define MAX_ORDER_VALUE 250000
#define MAX_STRING_LENGTH 20
#define MAX_MONTH 12
#define MIN_MONTH 1
#define MAX_YEAR 2013
#define MIN_YEAR 2000
#define LONG_MONTH 31
#define SHORT_MONTH 30
#define FEBRUARY 29

class date
{
 public:
    date(string fullDate);
    date();
    int year;
    int month;
    int day;
};

class customer
{
 public:
  customer(string newName, string newLocation, string newDateFirstOrder, string newDateLastOrder, int newValueLastOrder, int newValueTotalOrder);
  customer();
  void getName(string& name);
  void getLocation(string& location);
  void getDateFierstOrder();
  void getDateLastOrder();
  int  getValueLastOrder();
  int  getValueTotalOrder;
  //void print();
 private:
  string name;
  string location;
  date dateFirstOrder;
  date dateLastOrder;
  int  valueLastOrder;
  int  valueTotalOrder;
};


int main()
{
  customer customerList[MAX_CUSTOMERS];
  
  customerList[1] = customer("Boeing",   "California", "2009-03-29", "2013-05-13", 10000,  50000);
  customerList[2] = customer("Boeing",   "Washington", "2007-10-05", "2012-01-23", 25000,  130000);
  customerList[3] = customer("Lockheed", "Denver",     "2005-07-20", "2013-08-11", 100000, 120000);
  customerList[4] = customer("Lockheed", "California", "2010-04-29", "2012-12-29", 45000,  175000);
  customerList[5] = customer("Lockheed", "Florida",    "2012-11-02", "2012-11-02", 75000,  110000);
  customerList[6] = customer("Harris",   "Florida",    "2011-09-17", "2013-02-21", 5000,   60000);
  customerList[7] = customer("Raytheon", "California", "2004-06-12", "2012-06-30", 100000, 200000);
  customerList[8] = customer("Northrop", "Maryland",   "2010-07-07", "2013-02-15", 30000,  120000);
  customerList[9] = customer("BAE",      "Virginia",   "2009-03-29", "2013-05-13", 20000,  80000);
  
  cout<< "poop";
      
  return 0;
}
 
date::date(string fullDate)
            {year = 1;
             month = 2;
             day = 3;
            } 
            
date::date()
           {
               
           }
 
customer::customer(string newName, string newLocation, string newDateFirstOrder, string newDateLastOrder, int newValueLastOrder, int newValueTotalOrder)
          :name(newName), location(newLocation), valueLastOrder(newValueLastOrder), valueTotalOrder(newValueTotalOrder)
             {
                  dateFirstOrder = date(newDateFirstOrder);
                  dateLastOrder = date(newDateLastOrder);
             }
             
customer::customer()
            {
                
            }
             