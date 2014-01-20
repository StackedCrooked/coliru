#include <map>
#include <string>
using namespace std;

struct ap_pair {
    ap_pair(float tp, float tm) : total_price(tp), total_amount(tm) {};
    ap_pair & operator+=(const ap_pair &);
    float total_price;
    float total_amount;
};

int main()
{
    map<string, ap_pair> mymap;
    
    string name = "hi";
    float num1 = 3, num2 = 4;
    
    ap_pair myobj(num1, num2); //send the weight/count and per unit price ap_pair 
    mymap.insert(pair<string,ap_pair>(name, myobj(num1, num2)));
}