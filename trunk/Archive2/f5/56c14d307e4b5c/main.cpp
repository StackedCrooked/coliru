#include "boost/date_time/posix_time/posix_time.hpp" 

int main()
{
using namespace boost::posix_time;

ptime now = time_duration td(1,2,3);
ptime late = now+hours(5);

cout << ( now - later );


return 0;
}