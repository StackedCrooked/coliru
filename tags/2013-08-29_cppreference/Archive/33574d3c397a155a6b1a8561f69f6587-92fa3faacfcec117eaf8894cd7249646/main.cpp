#include <iostream>
using namespace std;
int main()
{



char sel;
string x;
string password1;


cout<<"enter text you want to encrypt or decryp\n";

getline( cin, x );

cout<<"enter password\n";
//std::cin.get();
cin >> password1;

//std::cout << std::cin.gcount() << " characters read: ";

if(password1=="password")
{


cout<<"type e to encrypt, and d to decrypt \n";
cin >> sel;

//////////////////////////////
if (sel == 'e' || sel == 'E')
{

//conversion
for(int i = 0; i < x.length(); i++)
{

if (x[i] == 'a' || x[i] == 'A')
cout<<"4";

else if (x[i] == 'b' || x[i] == 'B')
cout<<"8";

else if (x[i] == 'c' || x[i] == 'C')
cout<<"(";

else if (x[i] == 'd' || x[i] == 'D')
cout<<")";

else if (x[i] == 'e' || x[i] == 'E')
cout<<"3";

else if (x[i] == 'f' || x[i] == 'F')
cout<<":";

else if (x[i] == 'g' || x[i] == 'G')
cout<<"6";

else if (x[i] == 'h' || x[i] == 'H')
cout<<"-";

else if (x[i] == 'i' || x[i] == 'I') 
cout<<"1";

else if (x[i] == 'j' || x[i] == 'J')
cout<<"/";

else if (x[i] == 'k' || x[i] == 'K')
cout<<"<";

else if (x[i] == 'l' || x[i] == 'L')
cout<<"|";

else if (x[i] == 'm' || x[i] == 'M')
cout<<"|'|";

else if (x[i] == 'n' || x[i] == 'N')
cout<<"/\\";

else if (x[i] == 'o' || x[i] == 'O')
cout<<"0";

else if (x[i] == 'p' || x[i] == 'P')
cout<<"|^";

else if (x[i] == 'q' || x[i] == 'Q')
cout<<"9";

else if (x[i] == 'r' || x[i] == 'R')
cout<<"?";

else if (x[i] == 's' || x[i] == 'S')
cout<<"5";

else if (x[i] == 't' || x[i] == 'T')
cout<<"7";

else if (x[i] == 'u' || x[i] == 'U')
cout<<"_";

else if (x[i] == 'v' || x[i] == 'V')
cout<<">";

else if (x[i] == 'w' || x[i] == 'W')
cout<<"|,|";

else if (x[i] == 'x' || x[i] == 'X')
cout<<"%";

else if (x[i] == 'y' || x[i] == 'Y')
cout<<"'/";

else if (x[i] == 'z' || x[i] == 'Z')
cout<<"2";

else if (x[i] == ' ' || x[i] == ',' || x[i] == '.')
cout<<".";

else if (x[i] == '1')
cout<<"\"1\"";

else if (x[i] == '2')
cout<<"\"2\"";

else if (x[i] == '3')
cout<<"\"3\"";

else if (x[i] == '4')
cout<<"\"4\"";

else if (x[i] == '5')
cout<<"\"5\"";

else if (x[i] == '6')
cout<<"\"6\"";

else if (x[i] == '7')
cout<<"\"7\"";

else if (x[i] == '8')
cout<<"\"8\"";

else if (x[i] == '9')
cout<<"\"9\"";

else if (x[i] == '0')
cout<<"\"0\"";


else
{
for(int o=0;o<10000;o++)
cout<<endl;
i = 10 +  x.length();
cout<<"you have entered invalid text, make sure there are no special characters\n";
}
}

cout<<endl;   
   
}
///////////////////////////////////////////////////////
else if (sel == 'd' || sel == 'D')
{

//conversion
for(int i = 0; i < x.length(); i++)
{

if (x[i] == '4' && x[i+1] != '\"' && x[i-1] != '\"')
cout<<"A";

if (x[i] == '8' && x[i+1] != '\"' && x[i-1] != '\"')
cout<<"B";

if (x[i] == '(')
cout<<"C";

if (x[i] == ')')
cout<<"D";

if (x[i] == '3' && x[i+1] != '\"' && x[i-1] != '\"')
cout<<"E";

if (x[i] == ':')
cout<<"F";

if (x[i] == '6' && x[i+1] != '\"' && x[i-1] != '\"')
cout<<"G";

if (x[i] == '-')
cout<<"H";

if (x[i] == '1' && x[i+1] != '\"' && x[i-1] != '\"') 
cout<<"I";

if (x[i] == '/' && x[i+1] != '\\' && x[i-1] != '\'')
cout<<"J";

if (x[i] == '<')
cout<<"K";

if (x[i] == '|' && x[i+1] != ',' && x[i-1] != ',' && x[i+1] != '\'' && x[i-1] != '\'' && x[i+1] !='^')
cout<<"L";

if (x[i] == '|' && x[i+1] == '\'' && x[i+2]=='|')
cout<<"M";

if (x[i] == '/' && x[i+1] == '\\')
cout<<"N";

if (x[i] == '0' && x[i+1] != '\"' && x[i-1] != '\"')
cout<<"O";

if (x[i] == '|' && x[i+1] == '^')
cout<<"P";

if (x[i] == '9' && x[i+1] != '\"' && x[i-1] != '\"')
cout<<"Q";

if (x[i] == '?')
cout<<"R";

if (x[i] == '5' && x[i+1] != '\"' && x[i-1] != '\"')
cout<<"S";

if (x[i] == '7' && x[i+1] != '\"' && x[i-1] != '\"')
cout<<"T";

if (x[i] == '_')
cout<<"U";

if (x[i] == '>')
cout<<"V";

if (x[i] == '|' && x[i+1] == ',' && x[i+2]=='|')
cout<<"W";

if (x[i] == '%')
cout<<"X";

if (x[i] == '\'' && x[i+1] == '/')
cout<<"Y";

if (x[i] == '2' && x[i+1] != '\"' && x[i-1] != '\"')
cout<<"Z";

if (x[i] == '.')
cout<<" ";

//numbers

if (x[i] == '1' && x[i+1] == '\"' && x[i-1]=='\"')
cout<<"1";

if (x[i] == '2' && x[i+1] == '\"' && x[i-1]=='\"')
cout<<"2";

if (x[i] == '3' && x[i+1] == '\"' && x[i-1]=='\"')
cout<<"3";

if (x[i] == '4' && x[i+1] == '\"' && x[i-1]=='\"')
cout<<"4";

if (x[i] == '5' && x[i+1] == '\"' && x[i-1]=='\"')
cout<<"5";

if (x[i] == '6' && x[i+1] == '\"' && x[i-1]=='\"')
cout<<"6";

if (x[i] == '7' && x[i+1] == '\"' && x[i-1]=='\"')
cout<<"7";

if (x[i] == '0' && x[i+1] == '\"' && x[i-1]=='\"')
cout<<"0";

if (x[i] == '8' && x[i+1] == '\"' && x[i-1]=='\"')
cout<<"8";

if (x[i] == '9' && x[i+1] == '\"' && x[i-1]=='\"')
cout<<"9";

}

cout<<endl;   
   
}
/////////////////////////////////////////////////

else 
cout<<"sorry you have entered wrong choice\n";
}

else
cout<<"not matched password\n";

return 0;
}



