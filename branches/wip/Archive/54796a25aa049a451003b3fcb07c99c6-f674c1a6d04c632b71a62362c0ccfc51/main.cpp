#include <iostream>
#include <string>
#include <map>
#include <cstdint>
#include <tuple>

//aliases to reduce verbosity
using FIRST_NAME = std::string;
using LAST_NAME = std::string;
using STATE = std::string;

//define our customer record
using Customer = std::tuple<FIRST_NAME, 
                            LAST_NAME, 
                            STATE>;  
                            
enum class BadGood {bad, good};

int main()
{   

//Create our customers
Customer td = std::make_tuple(std::string{"Tony"}, 
                              std::string{"DaSilva"}, 
                              std::string{"NY"}); 
                                
Customer jb = std::make_tuple(std::string{"Jeff"}, 
                              std::string{"Beyer"}, 
                              std::string{"MI"}); 

//create & populate our database
std::map<Customer, BadGood> myCustomers{{td,BadGood::good},
                                        {jb, BadGood::bad}};

//create a test customer
Customer testCust = std::make_tuple(std::string{"Anthony"}, 
                                    std::string{"Wiener"}, 
                                    std::string{"NY"}); 

//Is the test customer in our database?
if(myCustomers.find(testCust) == myCustomers.end()) {
    
    std::cout << "Customer not already on list - set to \"good\"\n";
    
    myCustomers[testCust] = BadGood::good;
}

 std::cout << "DONE!\n";
}
