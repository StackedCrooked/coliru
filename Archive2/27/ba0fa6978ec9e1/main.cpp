// stringstreams
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
    string mystr;
    int price = 0;
    int quantity = 0;
    auto total = [&]() { return price * quantity; };

    cout << "------------------------------------------------------" << '\n';
    cout << "-----------------Welcome to the shop!-----------------" << '\n';
    cout << "------------------------------------------------------" << '\n';
    cout << "Enter price of item" << '\n';
    getline(cin, mystr);
    stringstream(mystr) >> price;
    cout << "How Many do you want?" << '\n';
    getline(cin, mystr);
    stringstream(mystr) >> quantity;
    
    cout << "you want this many: " << quantity << '\n';
    cout << "at this price: " << price << '\n';
    cout << "this would cost you: " << total() << " pounds" << '\n';

    if (total() >= 20)
    {
        cout << "here is a discount of " << total() / 20 << '\n';
    }
    else if (total() >= 10)
    {
        cout << "here is a discount of " << total() / 10 << '\n';
    }
    else
    {

        cout << "sorry no discount" << '\n';
    };
}