// TestEd.cpp
//
// Breaking a string into susbtring using Boost Strig Algo lib.
//
// DJD & the Wilmott team spirit
//
// http://stacked-crooked.com/view?id=acf028cae381e72678a07e6dc610852b

#include <string>
#include <vector>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <tuple>

int main()
{  
    
     std::string SuperEdString("2013-02-01,54.87,55.20,54.67,54.92,2347600,54.92");
     
     // Outer machinery
     std::vector<std::string> outerArray;
     boost::split(outerArray, SuperEdString, boost::is_any_of(",")); 
     
     // Inner machinery
     std::tuple<std::string, std::string,  std::string> result;
     std::vector<std::string> innerArray;
     
     boost::split(innerArray, outerArray[0],boost::is_any_of("-")) ;
     result = std::make_tuple( innerArray[0], innerArray[1], innerArray[2] );
     
     // innerArray
     std::cout << "Year:\t\t" << std::get<0>(result) << std::endl;
     std::cout << "Month:\t\t" << std::get<1>(result) << std::endl;
     std::cout << "Day:\t\t" << std::get<2>(result) << std::endl;
     
     // outerArray
      std::cout << "Open:\t\t" << outerArray[1] << std::endl;
      std::cout << "High:\t\t" << outerArray[2] << std::endl;
      std::cout << "Low:\t\t" << outerArray[3] << std::endl;
      std::cout << "Close:\t\t" << outerArray[4] << std::endl;
      std::cout << "Volume:\t\t" << outerArray[5] << std::endl;
      std::cout << "Adj.Close:\t" << outerArray[6] << std::endl;
           

    return 0;
}
