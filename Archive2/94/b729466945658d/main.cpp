#include <string>
struct Date {};
using namespace std;
class Person{
public:
    Person( const string&, const string&, long long, const Date& );
    void set( const string&, const string&, long long, const Date& );

private:
    char name [31];
    char last_name [31];
    long long national_code ; //long long for storing a 10 digit number
    Date birthday;
};

using namespace std;
class Aircrew: public Person
{
public:
    //copy-constructor
    Aircrew( const string&, const string&, long long, const Date&,
             long long, const Date& );
    //Set member data
    void set( long long, const Date& );
private:
    //long long used to be sure about 10digit numbers and more
    long long personal_code;
    // date of employment
    Date employ_date;
};

using namespace std;

Aircrew::Aircrew( const string& n, const string& ln, long long ncode,
                  const Date& D_b, long long pcode,const Date& D_e )
        :Person( n, ln, ncode, D_b ) //base class constructor
{set( pcode, D_e );}
void Aircrew::set(long long pcode, const Date& D_e )
{
    personal_code = pcode;
    employ_date = D_e; //assignment operator( = ) is overloaded for Date class
}