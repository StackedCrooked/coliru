 #include <iostream>

using namespace std;


void compute_coins(int change, int quarters, int dimes, int nickels, int pennies);
void output(int quarters, int dimes, int nickels, int pennies);

int main()
{
int change, quarters, dimes, nickels, pennies;
char again = 'y';

cout << "Welcome to the change dispenser!\n";

while(again == 'y'){//Creating loop to allow the user to repeat the process
cout << "Please enter the amount of cents that you have given between 1 and 99\n";
cin >> change;
while((change < 0) || (change >100)){//Making a loop to make sure a valid number is             inputed
        cout << "Error: Sorry you have entered a invalid number, please try again:";
        cin >> change;
}
cout << change << " Cents can be given as: " << endl;
 compute_coins(change, quarters, dimes, nickels, pennies);
 output(quarters, dimes, nickels, pennies);


 cout << "Would you like to enter more change into the change dispenser?  y/n\n";//prompts the user to repeat this process
cin >> again;


}
return 0;
}


void compute_coins(int change, int quarters, int dimes, int nickels, int pennies) {//calculation to find out the amount of change given for the amount inpuied
    using namespace std;
    quarters = change / 25;
    change = change % 25;
    dimes = change / 10;
    change = change % 10;
    nickels = change / 5;
    change = change % 5;
    pennies = change;
    return ;
}

void output(int quarters, int dimes, int nickels, int pennies){
using namespace std;
cout << "Quarters = " << quarters << endl;
cout << "dimes = " << dimes << endl;
cout << "nickels = " << nickels << endl;
cout << "pennies = " << pennies << endl;}