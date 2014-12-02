#include <iostream>
using namespace std;
 
void Last() // called by Third()
{
    cout << "Start Last" << endl;
    cout << "Last throwing int exception" << endl;
    throw -1;
    cout << "End Last" << endl;
 
}
 
void Third() // called by Second()
{
    cout << "Start Third" << endl;
    Last();
    cout << "End Third" << endl;
}
 
void Second() // called by First()
{
    cout << "Start Second" << endl;
    try
    {
        Third();
    }
    catch(double)
    {
         cerr << "Second caught double exception" << endl;
    }
    cout << "End Second" << endl;
}
 
void First() // called by main()
{
    cout << "Start First" << endl;
    try
    {
        Second();
    }
    catch (int)
    {
         cerr << "First caught int exception" << endl;
    }
    catch (double)
    {
         cerr << "First caught double exception" << endl;
    }
    cout << "End First" << endl;
}
 
int main()
{
    cout << "Start main" << endl;
    try
    {
        First();
    }
    catch (int)
    {
         cerr << "main caught int exception" << endl;
    }
    cout << "End main" << endl;
 
    return 0;
}