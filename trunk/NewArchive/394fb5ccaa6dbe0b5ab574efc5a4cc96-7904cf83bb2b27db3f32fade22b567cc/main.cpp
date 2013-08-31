/* Project Part One - take number string and return number value */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <string>
#include <cctype>
using namespace std;
int main () {
// ****** first method ********
int i=0, current_number, new_number, integer_value;
char  num_string[] = "558877", char_num_string[]="331133";
cout << "**  This is the First Method  **" << endl;
while (i <= 5){ 
current_number = (num_string[i] - '0');
if (i == 0)
{ new_number = current_number;
} 

else
{ new_number = current_number + new_number*10;}
cout << "each step of calculation  " << new_number << endl;
i = i + 1;
}
cout << "the Integer is                             " << new_number << endl;
cout << "test line, add 111111 to original string   " << new_number+111111 << endl;
//system("pause");
getchar();

// ******** Second Method *********
  if (isdigit(char_num_string[0]))
  {
    integer_value = atoi (char_num_string);
     cout      <<'\n';
    cout << "**  This is the Second Method  **" << endl;
    cout <<"The value of the number string is  " << integer_value << endl;
    
    // the following line is to prove the vaule returned is an integer and
    // not a character
    cout <<"Test line, add 111111 =            " << integer_value+111111 << endl;
  }
return 0;
}