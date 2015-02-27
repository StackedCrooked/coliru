#include <iostream>

using namespace std;

class numDays {

private: // member variables
int hours;
double days;

public: // member functions

numDays(int h = 0) {
    hours = h;
    days = h / 8.0;
}

void setHours(int s) {
    hours = s;
    days = s / 8.0;
}

double getDays() {
    return days;
}

numDays operator+(numDays& obj) {
    return numDays(hours + obj.hours);
}

numDays operator- (numDays& obj) { // Overloaded subtraction
    return numDays(hours - obj.hours);
 }

numDays operator++ () { // Overloaded prefix increment
    numDays temp_obj(hours);
    ++hours;
    days = hours / 8.0;
    return temp_obj;

}
numDays operator++ (int) { // Overloaded postfix increment
    numDays temp_obj(hours);
    hours++;
    days = hours / 8.0;
    return temp_obj;
}
numDays operator-- () { // Overloaded prefix decrement
    numDays temp_obj(hours);
    --hours;
    days = hours / 8.0;
    return temp_obj;
}
numDays operator-- (int) { // Overloaded postfix decrement
    numDays temp_obj(hours);
    hours--;
    days = hours / 8.0;
    return temp_obj;
}
};


int main() {
// insert code here...
numDays one(25), two(15), three, four;

// Display one and two.
cout << "One: " << one.getDays() << endl;
cout << "Two: " << two.getDays() << endl;
// Add one and two, assign result to three.
three = one + two;
// Display three.
cout << "Three: " << three.getDays() << endl;
// Postfix increment...
four = three++;
cout << "Four = Three++: " << four.getDays() << endl;
// Prefix increment...
four = ++three;
cout << "Four = ++Three: " << four.getDays() << endl;
// Postfix decrement...
four = three--;
cout << "Four = Three--: " << four.getDays() << endl;
// Prefix increment...
four = --three;
cout << "Four = --Three: " << four.getDays() << endl;
return 0;
}