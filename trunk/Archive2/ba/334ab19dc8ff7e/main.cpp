// Skeleton
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class account {
    private:
	string name; // a field ("member" in C++)
	double balance; // missing balance field

	public:
	account(string customer) : name(customer) {} // a constructor
	account(string customer, double b) : name (customer), balance(b) {} // missing balance initialisation

	string get_name() const { return name; } // a method
	double get_balance() {return balance; } 
    
    void deposit (double amount) { 
        balance = balance + amount; } 
        
        void withdraw (double amount) { 
            balance = balance - amount; } 
    
}; // Note the ; at the end of the class - needed!

int main() {
	account jim("Jim");
	account jam("Jam", 1000000);

    cout << jim.get_name() << '\n'; 
	cout << jam.get_name() << '\n';
    cout << jam.get_balance() << '\n'; 
     cin << jam.deposit()<<   '\n';
	cout << jam.get_balance() << '\n'; 

	return 0;
}