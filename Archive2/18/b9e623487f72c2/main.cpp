#include <iostream>
#include <string>

bool jump(const std::string& to)
{
    std::cout << "jump to loop " << to << "? " ;
    char jump = 'n';
    if( std::cin >> jump ) {
        std::cout << "answer: '" << jump << "'\n" ;
        return ( jump == 'y' || jump == 'Y' );
    } else exit(0) ;
}


int main()
{
    bool first_loop = true;
    //Loop counter changes in loop body
    for(int con_negative = 0; con_negative < 5; ++con_negative) {
        if( first_loop) {
            std::cout << "loop one begin \n" ;
            std::cout << "first part of loop one code\n" ;

            if( jump("two") ) {
    			con_negative = -1; //Will be incremented to 0 at start of next iteration
                first_loop = !first_loop;
                continue ;
            }
            std::cout << "second part of loop one code\n" ;
            std::cout << "loop one end \n" ;
        }  else {
            std::cout << "loop two begin \n" ;
            std::cout << "first part of loop two code\n" ;

            if( jump("one") ) {
				con_negative = -1; //Will be incremented to 0 at start of next iteration
                first_loop = !first_loop;
                continue ;
            }
            std::cout << "second part of loop two code\n" ;
            std::cout << "loop two end \n" ;
        }
    }
}