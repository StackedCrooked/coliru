// inserting into a vector
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/variant.hpp>
using namespace std;

template< class T>
class ThreadSafeFromString
{
    private:
        bool isFloat( const string& myString ) 
        {
            std::istringstream iss(myString);
            float f;
            iss >> noskipws >> f; // noskipws considers leading whitespace invalid
            // Check the entire string was consumed and if either failbit or badbit is set
            return iss.eof() && !iss.fail(); 
        }
        bool isDouble( const string& myString ) 
        {
            std::istringstream iss(myString);
            double d;
            iss >> noskipws >> d; // noskipws considers leading whitespace invalid
            // Check the entire string was consumed and if either failbit or badbit is set
            return iss.eof() && !iss.fail(); 
        }
      
    public:
        static T convert( const std::string& value)
        {
            if( value.empty())
                return T();
            else if ( isFloat(value) )
            {
                return boost::lexical_cast<float>( value);
            }
            else if ( isDouble(value) )
            {
                return boost::lexical_cast<double>( value);
            }
            else
            {
                try
                {
                    return boost::lexical_cast<T>( value);
                }
                catch ( boost::bad_lexical_cast& blc)
                {
                    std::cout << "Casting " << value << " to " << typeid(T).name() << endl; 
                    std::cout << "Bad lexical cast" << endl;            
                    return T();
                }
                catch(...)
                {
                    std::cout << "Another error." << endl;
                    return T();
                    //throwError( typeid(T).name(), value.c_str());
                }
            }
        }
};

int main ()
{
  std::string str = "12.20";
  std::cout << "Converting: " << str << endl;;
  int integer = ThreadSafeFromString<int>::convert(str);
  float f     = ThreadSafeFromString<float>::convert(str);
  std::cout << "As Integer: " << integer << endl;
  std::cout << "As Float: "   << f       << endl;
  try 
  {
    std::cout << "Number: " << boost::numeric_cast<int>(ThreadSafeFromString<double>::convert(str));    
  }
  catch (boost::numeric::positive_overflow& pof)
  {
    std::cout << "Integer ex: " << integer << endl;
    std::cout << pof.what() << endl << "Value: " << std::numeric_limits<float>::max();  
  }
  return 0;
}