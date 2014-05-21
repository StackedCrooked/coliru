#include <fstream> // <fstream.h>
#include <iostream> // <iostream.h>
#include <map> // <map.h>
#include <string>
//#include <iterator>
//#include <cstdlib>
#include <iomanip>
//#include <conio.h>

typedef std::map<std::string, int> StrIntMap; // map for counting

// prefer value sematics over reference semantivs
// void countWords(std::istream& in, StrIntMap& words) // func that count words
StrIntMap countWords( std::istream& in )
{
    StrIntMap words ;
    std::string s;

    while (in >> s)
    {
        ++words[s];
    }
    
    return words ;
}

// using namespace std;

int main ()
{
  // char str [80];
  
  {
      std::ofstream out("test.dat");
      if(!out) {
    	std::cout << "Cannot open file.\n";
		return 1;
      }
      /* 
      do {
            cout << "Enter a word (BL to quit):\n";
            cin >> str;
            out << str;
            } while(*str != '\n'); // if empty str inputed -> stop do-while
      out.close();
      */
      
      std::string str ;
      while( std::cout << "Enter a word (BL to quit): " && 
             std::cin >> str &&
             !str.empty() ) out << str << '\n' ; // separate with white space
  }

  std::ifstream in("test.dat");
    if(!in) {
		std::cout << "Cannot find file.\n";
		return 1;
    }

  /* 
  StrIntMap w;
  countWords(in, w);
  */
  StrIntMap w = countWords(in) ;
  
    for (StrIntMap::iterator p = w.begin( ); p != w.end( ); ++p)
    {   //std::cout << "\nPress any key to close";
        std::cout << std::setw(30) << std::left  << p->first  << " occurred "
                  << std::setw(10)  << std::right << p->second << " times.\n";
    }

  std::cout << "\nPress any key to close";

  // getch();
  // return 0;
}
