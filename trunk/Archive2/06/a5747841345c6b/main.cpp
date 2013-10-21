# include <iostream>
# include <iomanip>
using namespace std;

ostream &manip(ostream &stream)
{
cout.setf(ios::showpos);// Works fine
cout.setf(ios::hex, ios::basefield);// Does not work
}

int main()
{
int nbr=18;
manip(cout);
cout << nbr << endl;

return 0;
} 
