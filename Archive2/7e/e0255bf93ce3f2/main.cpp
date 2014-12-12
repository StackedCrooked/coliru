#include <list>
#include <iostream>

using namespace std;

int main()
{
    list<int> l;
    int count;
    cout << "Enter number of elements you want to insert into the list.";
    cin >> count;
    
    for (int i = 0 ;i < count; i++)
    {
        int val;
        cout << "\n Enter a Value .";
        cin >> val;
        
        l.push_front(val);
    }
    list<int>::iterator it = l.begin();
    for ( ;it != l.end(); it++ )
    {
        cout << " " << *it << ",\n";
    }
    l.sort();
    cout << "\n List after Sort \n";
    it = l.begin();
    for ( ;it != l.end(); it++ )
    {
        cout << " " << *it << ",\n";
    }
    return 0;
}