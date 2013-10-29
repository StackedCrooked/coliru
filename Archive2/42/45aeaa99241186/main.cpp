#include <iostream>
#include <list>

using namespace std;




using namespace std;

template <typename T>
list<T> interleaveLists(const list<T>& l, const list<T>& m)
{
    list<T> interleavedList;
    typename list<T>::const_iterator iter1;
    typename list<T>::const_iterator iter2;
    typename list<T>::const_iterator iter3;
    typename list<T>::const_iterator iter4;

    iter1 = l.begin();
    iter2 = l.end();
    iter3 = m.begin();
    iter4 = m.end();

    while (iter1 != iter2 || iter3 !=iter4)
    {
        interleavedList.push_back(*iter1);
        interleavedList.push_back(*iter3);
        iter1++;
        iter3++;

        if (iter1 == iter2)
        {
            interleavedList.push_back(*iter3);
        }

        if (iter3 == iter4)
        {
            interleavedList.push_back(*iter1);
        }
    } // end while
    return interleavedList;
} //end interleaveLists

//******************************************************************

int main()
{
    list<int> list1;
    list<int> list2;
    list<int> list3;
    list<int> newList;

    // Create list1 = {40, -5, 66, -7, 8}
    list1.push_back(40);
    list1.push_back(-5);
    list1.push_back(66);
    list1.push_back(-7);
    list1.push_back(8);

    // Create list2 = {22, 3, -4}
    list2.push_back(22);
    list2.push_back(3);
    list2.push_back(-4);

    newList = interleaveLists(list1, list2);
    while (!newList.empty())
    {
        cout << newList.front() << " ";
        newList.pop_front();
    }
    cout << endl;

    newList = interleaveLists(list3, list2);
    while (!newList.empty())
    {
        cout << newList.front() << " ";
        newList.pop_front();
    }
    cout << endl;
} // end main