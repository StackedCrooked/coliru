#include <iostream>
using namespace std ;

char *strstr(char *str1, const char *str2)
{
    int count2= 0, count2_max= 0 ;

	while (*(str2) != '\0') //recording max value of 2nd string
	{
		str2++ ;
		count2_max++ ;
	}
	str2 -= count2_max ;
	while (*(str1) != '\0') //checking string 1 character by character for if it has string 2 in it.
	{
		if (*(str2) == *(str1))
		{
			str2++ ;
			count2++ ;
		}
		else
		{
			if (*(str1) != *(str1-1))
			{
				count2= 0 ;
			}
		}

		if (count2 == count2_max) //checking if 2nd string is complete in the first string
		{
			str1=((str1-count2_max) + 1) ;
			return 	str1 ;
		}
		str1++ ;
	}
	if (*(str1) == '\0')
	{
		return NULL ;
	}
}

int main()
{
	char *str1= new char[100] ; //The first string
	char *str2= new char[100] ; //The second string

	cout << "Please Enter the string: " ; cin.getline(str1, 100) ;
	cout << "Now please enter the second string: " ; cin.getline(str2, 100) ;

	cout << endl << "The pointer to the first occured second string (str2) in the first string (str1) holds the following address: " << (int*)strstr(str1, str2) << endl << endl ;

	delete []str1 ;
	delete []str2 ;
}
