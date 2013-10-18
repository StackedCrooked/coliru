#include <iostream>
#include <string>

struct Sales_data 
{
    std::string Book_Name;
    unsigned Units_Sold = 0;
    double Revenue = 0.0;
};

int main()
{
    double price;
    Sales_data total;  // variable to hold data for the next transaction // read the first transaction and ensure that there are data to process
    if (std::cin >> total.Book_Name >> total.Units_Sold >> price) 
    {
        total.Revenue = total.Units_Sold * price;
        Sales_data trans; // variable to hold the running sum // read and process the remaining transactions
        while (std::cin >> trans.Book_Name >> trans.Units_Sold >> price) 
        {
            trans.Revenue = trans.Units_Sold*price;
            // if we're still processing the same book
            if (total.Book_Name == trans.Book_Name)
            {
                total.Units_Sold += trans.Units_Sold; // update the running 
                total.Revenue += trans.Revenue; // update the running 
            }
            else 
            {
            std::cout << total.Book_Name << total.Units_Sold << total.Revenue;
            ￼￼total.Book_Name = trans.Book_Name;
            total.Units_Sold = trans.Units_Sold;
            ￼￼total.Revenue = trans.Revenue;
            }
            std::cout << total.Book_Name << total.Units_Sold << price << std::endl;//print the last transaction 
        }
    }
    else 
    {
        // no input! warn the user
        std::cerr << "No data?!" << std::endl; 
        return -1; // indicate failure
    }
    return 0; 
}