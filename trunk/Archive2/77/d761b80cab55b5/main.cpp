#include <vector>
#include <iostream>

const float HAMMERS_RATE = 10.99f ;
const float WRENCHES_RATE = 10.99f ;
const float LEVERS_RATE = 19.99f ;
const float TAPES_RATE = 4.99f ;
const float SCREW_DRIVERS_RATE = 8.99f ;

class Register
{
    std::vector<int> hammers ;
    std::vector<int> wrenches ;
    std::vector<int> levers ;
    std::vector<int> tapes ;
    std::vector<int> screw_drivers ;
    
    int              order_limit ;
    int              order_taken ;
    float            total_cost ;
    
public:
    Register(int ol) : order_limit{ol}, order_taken{0}, total_cost{0.0f} {}
    Register() {}
    
    void get_order();
    void return_receipts();
    
    friend Register operator+(const Register&, const Register&);
    
};

void Register::get_order()
{
    int input ;
    if(order_taken < order_limit)
    {
        std::cout << "Enter the number of quantities you want to take of each";
        std::cout << "\nHammers : ";
        std::cin >> input ;
        hammers.push_back(input);
        total_cost += static_cast<float>(input) * HAMMERS_RATE;
        
        std::cout << "\nWrenches : ";
        std::cin >> input ;
        wrenches.push_back(input);
        total_cost += static_cast<float>(input) * WRENCHES_RATE ;
        
        std::cout << "\nLevers : ";
        std::cin >> input ;
        levers.push_back(input);
        total_cost += static_cast<float>(input) * LEVERS_RATE ;
        
        std::cout << "\nTape Measures : ";
        std::cin >> input ;
        tapes.push_back(input);
        total_cost += static_cast<float>(input) * TAPES_RATE ;
        
        std::cout << "\nScrew Drivers : ";
        std::cin >> input ;
        screw_drivers.push_back(input);
        total_cost += static_cast<float>(input) * SCREW_DRIVERS_RATE ;
    
        ++order_taken ;
    }
}

void Register::return_receipts()
{
    for(unsigned int i = 0; i < hammers.size(); ++i)
    {
        std::cout << "Receipt #" << (i + 1) << " : \n" ;
        std::cout << "\t1. Hammers : " << hammers[i] << "\n" ;
        std::cout << "\t1. Wrenches : " << wrenches[i] << "\n" ;
        std::cout << "\t1. Levers : " << levers[i] << "\n" ;
        std::cout << "\t1. Tapes : " << tapes[i] << "\n" ;
        std::cout << "\t1. Screw Drivers : " << screw_drivers[i] << "\n\n" ;
    }
    
    std::cout << "Total Cost = $" << total_cost << std::endl ;
}
        
Register operator+(const Register& lhs, const Register& rhs)
{
    Register sum{0};
    sum.total_cost = lhs.total_cost + rhs.total_cost ;
    return sum ;
}

int main()
{
    Register r1{10}, r2{10}, r3 ;
    r1.get_order();
    r2.get_order();
    r3 = r1 + r2 ;
    r1.return_receipts();
    r2.return_receipts();
    r3.return_receipts();
    return 0;
}