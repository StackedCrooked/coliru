#include <iostream>


#if defined(ARDUINO)
#include "Arduino.h"

struct PlatformString {
    String value;
    
    PlatformString() 
        : PlatformString("")
    {
    };
    
    PlatformString(char const* val)
        : PlatformString(String(val))
    {
    };
    
    PlatformString(String val)
        : value { val } 
    {
    };
    
    
    PlatformString(bool val)
        : value { val ? "true" : "false" }
    {
    };
    
    PlatformString(int val)
        : value { String(val) } 
    {
    };
    
    PlatformString(double val)
        : PlatformString(val, 4) 
    {
    };
    
    PlatformString(double val, byte precision)
        : value { PlatformString::FloatToString(val, precision) } 
    {
    };
    
    PlatformString operator + (char const* s) {
        return PlatformString(this->value + String(s));
    };
    
    PlatformString operator + (const PlatformString &s) {
        return PlatformString(this->value + s.value);
    };
    
    operator String() { return this->value; }
    
    private:
        static String FloatToString(float val, byte precision) {
            // returns val with number of decimal places determine by precision
            // precision is a number from 0 to 6 indicating the desired decimial places
            // example: floatToString(3.1415, 2); // returns 3.14 (two decimal places)
        
        	String output = "";
        
        	if(val < 0.0){
        		output += "-";
        		val = -val;
        	}
        
        	output += int(val);  //prints the int part
        	if(precision > 0) 
        	{
        		output += "."; // print the decimal point
        
        		unsigned long frac;
        		unsigned long mult = 1;
        		byte padding = precision -1;
        		while(precision--)
        			mult *=10;
        
        		if(val >= 0)
        			frac = (val - int(val)) * mult;
        		else
        			frac = (int(val)- val ) * mult;
        		unsigned long frac1 = frac;
        
        		while( frac1 /= 10 )
        			padding--;
        		while(  padding--)
        			output += "0";
        
        		output += frac;
        	}
        
        	return output;
        };
};

#else
#include <string>

struct PlatformString {
    std::string value;
    
    PlatformString() 
        : PlatformString("")
    {
    };
    
    PlatformString(char const* val)
        : PlatformString(std::string(val))
    {
    };
    
    PlatformString(std::string val)
        : value { val } 
    {
    };
    
    
    PlatformString(bool val)
        : value { val ? "true" : "false" }
    {
    };
    
    PlatformString(int val)
        : value { std::to_string(val) } 
    {
    };
    
    PlatformString(double val)
        : value { std::to_string(val) } 
    {
    };
    
    PlatformString operator + (char const* s) {
        return PlatformString(this->value + std::string(s));
    };
    
    PlatformString operator + (const PlatformString &s) {
        return PlatformString(this->value + s.value);
    };
    
    operator std::string() { return this->value; }
};
#endif




PlatformString DoThing(int someNum) {
    PlatformString result = PlatformString("asdf ") + PlatformString(someNum) + " " + PlatformString(123.4567f) + " " + PlatformString(123.4567) + " " + PlatformString(true);
    return result;
}

int main()
{
    
    std::cout << DoThing(3).value << std::endl;
    
    return 0;
}

