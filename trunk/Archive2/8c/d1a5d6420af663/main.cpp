#include <iostream>
#include <memory>

class cStudent
{
public:
    bool shouldBeGraduated;
	int studentAge;

	cStudent( int age = last_objects_age )
	{
		last_objects_age = studentAge = age;
		shouldBeGraduated = studentAge > 18 ;
	}

	static int last_objects_age  ;
};

int cStudent::last_objects_age = 0 ;

int main()
{
    cStudent array[8] { 25 } ;
    for( const cStudent& s : array ) std::cout << s.studentAge << ' ';
    std::cout << '\n' ;

    const int n = 10 ;
    // http://en.cppreference.com/w/cpp/memory/unique_ptr
    std::unique_ptr< cStudent[] > array2( new cStudent[n] { 17 } ) ;
    for( int i = 0 ; i <n ; ++i ) std::cout << array2[i].studentAge << ' ';
    std::cout << '\n' ;

}
