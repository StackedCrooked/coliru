#include <iostream>
#include <forward_list>

using namespace std;

int main(void)
{
    forward_list<int> list1 = {1, 2, 3, 4, 5, 6};
    forward_list<int> list2;

    //Transfer elements between 2 and 5 from list1 to list2.    
    forward_list<int>::const_iterator iter_before = list1.before_begin();
    forward_list<int>::const_iterator iter = list1.begin();
    while ( iter != list1.end())
    {
        int item = *iter;
        cout << item ;
        if (2 <= item && item <= 5 )
        {
            auto iter_next = std::next(iter);
            list2.splice_after(list2.before_begin(),list1,iter_before);
            iter = iter_next;
            cout << "! "; // Indicates if current item is transferred.
        }
        else
        {
            iter++;
            iter_before++;
            cout << " ";
        }
    }

    cout << "\nList 1: ";
    for (auto item : list1)
    {
        cout << item << " ";
    }
    cout << "\nList 2: ";
    for (auto item : list2)
    {
        cout << item << " ";
    }
    cout << endl;

    return 0;
}