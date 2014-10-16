#include <iostream>
using std::cout;
using std::endl;

#include <ctime>
using std::time_t;
using std::tm;
using std::localtime;
 
int main()
{
    std::time_t timesecs = time ( nullptr );
   
    tm *calendar_time = localtime ( &timesecs );
    
    if( calendar_time != NULL )
    {
         std::cout << "local: " << std::asctime ( calendar_time ) << endl;;
    }
    else
    {
         exit( EXIT_FAILURE );
    }
    
    return 0;
}