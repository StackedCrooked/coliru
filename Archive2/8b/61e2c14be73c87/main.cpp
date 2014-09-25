#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string/predicate.hpp>

int a[3] {1,2,3};


int main()
{
/*    using boost::algorithm::starts_with;
    std::string server{"/server/foo"};
    if(starts_with(server, "/serve/"))
        std::cout << "yes";
    else
        std::cout << "no";
*/

 
    for(auto i : a) {
		std::cout << i <<std::endl;
	}
	return 0;
}

