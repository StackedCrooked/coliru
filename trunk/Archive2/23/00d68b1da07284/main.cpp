#include <cstdlib> // <stdlib.h> if ur using turbo C++
#include <iostream> // <iostream.h> if ur using turbo C++
#include <fstream> // <fstream.h> if ur using turbo C++
using namespace std; // remove this if ur using turbo C++

int main()
{
    const char* filename = "data.txt"; // the filename of the text file you want to create / read from
    
    /* ********************
     * Let's write some text into the file named "data.txt" (filename variable)
     */
    
    // since you want to WRITE to file, you should declare a variable of type ofstream
    ofstream fileOut( filename ); // open the file named "data.txt" (we passed the value of filename variable)
    // filename (data.txt) will be created if it doesn't exists    

    // write some data into fileOut (data.txt)
    fileOut << "Hello World !!" << " from C++ !!" << '\n';
    fileOut << "This is second line in file : " << filename << '\n';
    
    // close the file
    fileOut.close();
    
    /* ***********************
     * Now, we will READ the file named "data.txt" ( bali papalabasin natin ung nilagay natin sa kanya kanina na text )
     */
     
    // open the file "data.txt" for READING
    // you should use ifstream() class if you want to read from file
    ifstream fileIn( filename ); // open the file named "data.txt" for READING
    
    // ndi natin kailangan i2 para sa ofstream() kc, i-crecreate naman nya ung file if it doesn't exists :
    if( !fileIn ) // if file opening fails, then exit 
    {
        cerr << "File opening failed !!!\n";
        cerr << "Press ENTER to exit...\n";
        cin.get();
        exit( EXIT_FAILURE ); // <cstdlib> 
    }
    
    char strTemp[ 256 ]; // temporary variable, d2 maiistore ung ireread natin sa file (by word)
    
    // now read the datas WORD by WORD
    while( fileIn >> strTemp ) // loop until EOF or if file reading failed
    {
        cout << "The text read is : " << strTemp << '\n';
    }
    
    fileIn.close(); // close the file, ( optional )
    
    
    /* *****
     * ngaun, meron nang file na "data.txt" (tignan mu sa folder nung .exe mu)
     */
    return 0;
}