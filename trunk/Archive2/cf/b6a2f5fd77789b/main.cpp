#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class Food {
private:
    string category;
    string item;
    double price;
    int itemnum;
public:
    Food()
    : category(), item(), price(), itemnum() {}
    Food(string cat, string it, double pr, int itno)
    : category(cat), item(it), price(pr), itemnum(itno) {  }

    ostream& display(ostream& output) const{
        return output << category << "," << item << "," << price << "," << itemnum << '\n';
    }
    friend ostream& operator<<(ostream& output, Food const& f)
    {return f.display(output);}
    
    istream& scan(istream& input) {
        char delim;
        getline(input,category,','); //read until comma
        getline(input,item,',');
        input.ignore(1); //ignore comma
        input >> price >> delim >> itemnum;
        input.ignore(1); //ignore newline
        return input;
    }
    friend istream& operator>>(istream& input, Food& f)
    {return f.scan(input);}
};

int main() {
    istringstream fin(
        "main,steak bernaise,15,101\n"
        "pudding,banoffee,3.99,102\n"
        "starter,prawn cocktail,2.89,103\n"
        "drink,gin & tonic,3.50,104\n");
    
    vector<Food> _items;
    Food newFood;
    while(fin >> newFood)
        _items.push_back(newFood);
        
    for (size_t i = 0; i < _items.size(); ++i)
        cout << _items[i];
}