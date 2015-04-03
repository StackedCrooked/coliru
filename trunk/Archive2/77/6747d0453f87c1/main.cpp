    // http://stackoverflow.com/questions/29427273/distinguishing-between-an-int-and-a-double
    #include <iostream>
    #include <sstream>
    #include <cctype>
    #include <string>
    
    using namespace std;

    bool get_int( const string & input, int & i ) {
        stringstream ss(input);
        double d;
        bool isValid = ss >> d;
        if (isValid) {
            char c;
            while( ss >> c && isValid ) isValid = isspace(c);
            if (isValid) { 
                i = static_cast<int>(d);
                isValid = (d == static_cast<double>(i));
            }
        }
        return isValid;
    }
    
    int main( int argc, char *argv[] )
    {
        int creatLegs = 0;
        bool validLegs = false;

        do
        {
            string line;
            do {
                cout << "How many legs should the creature have? ";
            } while (not getline (cin,line));
         
            validLegs = get_int( line, creatLegs );

            if (creatLegs <= 0)
            {
                validLegs = false;
            }
            
            if (!validLegs)
            {
                cout << "Invalid value, try again." << endl;
            }
            
        } while (not validLegs);
        
        cout << "Got legs! (" << creatLegs << ")" << endl;
        
        return 0;
    }
