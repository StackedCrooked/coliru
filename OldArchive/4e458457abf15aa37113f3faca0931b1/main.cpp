#include <string>
#include <deque>
#include <iostream>
#include <algorithm>


using namespace std;


template<typename ContainerType>
void insert_elements( ContainerType& cont, int start, int finish )
{
    for( int num = start; num < finish; ++num )
    {
        cont.push_back( num );
    }
}

template<typename ContainerType>
void show_elements( ContainerType& cont, const string& prefix )
{
    cout << prefix << " : ";

    typename  ContainerType::const_iterator  iter = cont.begin();
    typename  ContainerType::const_iterator  end  = cont.end();    

    while( iter != end )
    {
        cout << *iter << " ";
        ++iter;
    }

    cout << endl;
}

int main()
{
    deque<int> coll;

    insert_elements( coll, 3, 9 );
    insert_elements( coll, 2, 6 );
    insert_elements( coll, 1, 8 );
    show_elements( coll, "unsorted      " );

    cout << "begin()+3 : " << *(coll.begin()+3) << endl;

    nth_element( coll.begin(),
        coll.begin()+3,
        coll.end() );
    show_elements( coll, "[1]nth_element" );

    return EXIT_SUCCESS;
}
