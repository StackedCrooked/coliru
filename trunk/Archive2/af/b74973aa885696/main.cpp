//GOOOD LUCK
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <Windows.h>
#include <stdlib.h>
#include <time.h> 
#include <random>
#include <cstdlib>

using namespace std;

int main()
{
    random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis1(1,28440);          // Died under 1 year of age.          1.161756638 % chance
	uniform_int_distribution<> dis2(1,4756);           // Died between 1-4 years of age.     0.194279696 % chance
	uniform_int_distribution<> dis3(1,2837);		   // Died between 5-9 years of age.     0.115889718 % chance
	uniform_int_distribution<> dis4(1,3765);		   // Died between 10-14 years of age.   0.153797951 % chance
	uniform_int_distribution<> dis5(1,13703);          // Died between 15-19 years of age.   0.559759184 % chance
	uniform_int_distribution<> dis6(1,20531);          // Died between 20-24 years of age.   0.838678816 % chance
	uniform_int_distribution<> dis7(1,19568);          // Died between 25-29 years of age.   0.799340854 % chance
	uniform_int_distribution<> dis8(1,22357);          // Died between 30-34 years of age.   0.913264801 % chance
	uniform_int_distribution<> dis9(1,31420);          // Died between 35-39 years of age.   1.283487819 % chance
	uniform_int_distribution<> dis10(1,53365);         // Died between 40-44 years of age.   2.179927672 % chance
	uniform_int_distribution<> dis11(1,79383);         // Died between 45-49 years of age.   3.242747089 % chance
	uniform_int_distribution<> dis12(1,104147);        // Died between 50-54 years of age.   4.254341371 % chance
	uniform_int_distribution<> dis13(1,127478);        // Died between 55-59 years of age.   5.207398478 % chance
	uniform_int_distribution<> dis14(1,147823);        // Died between 60-64 years of age.   6.038474388 % chance
	uniform_int_distribution<> dis15(1,172236);        // Died between 65-69 years of age.   7.035735454 % chance
	uniform_int_distribution<> dis16(1,226119);        // Died between 70-74 years of age.   9.236823110 % chance
	uniform_int_distribution<> dis17(1,307888);        // Died between 75-79 years of age.   12.57703684 % chance
	uniform_int_distribution<> dis18(1,378777);        // Died between 80-84 years of age.   15.47280922 % chance 
	uniform_int_distribution<> dis19(1,703169);        // Died at age 85 and above.          28.72402438 % chance 
	//REFERENCE: http://www.disastercenter.com/cdc/Death%20rates%202005.html

	int count = 0;


	for (count = 0; count < 2 && count > -1; count++)
	{
		if (dis1(gen) > 0 && dis1(gen) < 330)
		{

			cout << "\n\n\n\t\t\tYou Died! Better luck next time!" << "\n\n\n\t\t\t";
			cout << "T   "; Sleep(100);
			cout << "H   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "K   "; Sleep(100);
			cout << "S   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "F   "; Sleep(100);
			cout << "O   "; Sleep(100);
			cout << "R   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "P   "; Sleep(100);
			cout << "L   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "Y   "; Sleep(100);
			cout << "I   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "G   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "\n\n\n\t\t\t  ";
			return 0;
		}

		else
		{
			Sleep(360);
			cout << "\t\t\tIt's your birthday, you turned: " << count << "\n";
			count++;
		}
	}


	for (double count = 1; count < 5 && count >= 1; count++)
	{
		if (dis2(gen) > 1 && dis2(gen) < 9)
		{
			cout << "\n\n\n\t\t\tYou Died! Better luck next time!" << "\n\n\n\t\t\t";
			cout << "T   "; Sleep(100);
			cout << "H   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "K   "; Sleep(100);
			cout << "S   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "F   "; Sleep(100);
			cout << "O   "; Sleep(100);
			cout << "R   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "P   "; Sleep(100);
			cout << "L   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "Y   "; Sleep(100);
			cout << "I   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "G   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "\n\n\n\t\t\t  ";
			return 0;
		}

		else
		{
			Sleep(360);
			cout << "\t\t\tIt's your birthday, you turned: " << count << "\n";
			count++;
		}
	}


	for (double count = 4; count < 10 && count >= 4; count++)
	{
		if (dis3(gen) > 1 && dis3(gen) < 3)
		{
			cout << "\n\n\n\t\t\tYou Died! Better luck next time!" << "\n\n\n\t\t\t";
			cout << "T   "; Sleep(100);
			cout << "H   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "K   "; Sleep(100);
			cout << "S   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "F   "; Sleep(100);
			cout << "O   "; Sleep(100);
			cout << "R   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "P   "; Sleep(100);
			cout << "L   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "Y   "; Sleep(100);
			cout << "I   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "G   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "\n\n\n\t\t\t  ";
			return 0;
		}

		else
		{
			Sleep(360);
			cout << "\t\t\tIt's your birthday, you turned: " << count << "\n";
			count++;
		}
	}


	for (double count = 9; count < 15 && count >= 9; count++)
	{
		if (dis4(gen) > 1 && dis4(gen) < 5)
		{
			cout << "\n\n\n\t\t\tYou Died! Better luck next time!" << "\n\n\n\t\t\t";
			cout << "T   "; Sleep(100);
			cout << "H   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "K   "; Sleep(100);
			cout << "S   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "F   "; Sleep(100);
			cout << "O   "; Sleep(100);
			cout << "R   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "P   "; Sleep(100);
			cout << "L   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "Y   "; Sleep(100);
			cout << "I   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "G   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "\n\n\n\t\t\t  ";
			return 0;
		}

		else
		{
			Sleep(360);
			cout << "\t\t\tIt's your birthday, you turned: " << count << "\n";
			count++;
		}
	}


	for (double count = 14; count < 20 && count >= 14; count++)
	{
		if (dis5(gen) > 1 && dis5(gen) < 76)
		{
			cout << "\n\n\n\t\t\tYou Died! Better luck next time!" << "\n\n\n\t\t\t";
			cout << "T   "; Sleep(100);
			cout << "H   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "K   "; Sleep(100);
			cout << "S   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "F   "; Sleep(100);
			cout << "O   "; Sleep(100);
			cout << "R   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "P   "; Sleep(100);
			cout << "L   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "Y   "; Sleep(100);
			cout << "I   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "G   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "\n\n\n\t\t\t  ";
			return 0;
		}

		else
		{
			Sleep(360);
			cout << "\t\t\tIt's your birthday, you turned: " << count << "\n";
			count++;
		}
	}


	for (double count = 19; count < 25 && count >= 19; count++)
	{
		if (dis6(gen) > 1 && dis6(gen) < 172)
		{
			cout << "\n\n\n\t\t\tYou Died! Better luck next time!" << "\n\n\n\t\t\t";
			cout << "T   "; Sleep(100);
			cout << "H   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "K   "; Sleep(100);
			cout << "S   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "F   "; Sleep(100);
			cout << "O   "; Sleep(100);
			cout << "R   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "P   "; Sleep(100);
			cout << "L   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "Y   "; Sleep(100);
			cout << "I   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "G   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "\n\n\n\t\t\t  ";
			return 0;
		}

		else
		{
			Sleep(360);
			cout << "\t\t\tIt's your birthday, you turned: " << count << "\n";
			count++;
		}
	}


	for (double count = 24; count < 30 && count >= 24; count++)
	{
		if (dis7(gen) > 1 && dis7(gen) < 156)
		{
			cout << "\n\n\n\t\t\tYou Died! Better luck next time!" << "\n\n\n\t\t\t";
			cout << "T   "; Sleep(100);
			cout << "H   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "K   "; Sleep(100);
			cout << "S   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "F   "; Sleep(100);
			cout << "O   "; Sleep(100);
			cout << "R   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "P   "; Sleep(100);
			cout << "L   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "Y   "; Sleep(100);
			cout << "I   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "G   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "\n\n\n\t\t\t  ";
			return 0;
		}

		else
		{
			Sleep(360);
			cout << "\t\t\tIt's your birthday, you turned: " << count << "\n";
			count++;
		}
	}


	for (double count = 29; count < 35 && count >= 29; count++)
	{
		if (dis8(gen) > 1 && dis8(gen) < 204)
		{
			cout << "\n\n\n\t\t\tYou Died! Better luck next time!" << "\n\n\n\t\t\t";
			cout << "T   "; Sleep(100);
			cout << "H   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "K   "; Sleep(100);
			cout << "S   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "F   "; Sleep(100);
			cout << "O   "; Sleep(100);
			cout << "R   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "P   "; Sleep(100);
			cout << "L   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "Y   "; Sleep(100);
			cout << "I   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "G   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "\n\n\n\t\t\t  ";
			return 0;
		}

		else
		{
			Sleep(360);
			cout << "\t\t\tIt's your birthday, you turned: " << count << "\n";
			count++;
		}
	}


	for (double count = 34; count < 40 && count >= 34; count++)
	{
		if (dis9(gen) > 1 && dis9(gen) < 403)
		{
			cout << "\n\n\n\t\t\tYou Died! Better luck next time!" << "\n\n\n\t\t\t";
			cout << "T   "; Sleep(100);
			cout << "H   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "K   "; Sleep(100);
			cout << "S   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "F   "; Sleep(100);
			cout << "O   "; Sleep(100);
			cout << "R   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "P   "; Sleep(100);
			cout << "L   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "Y   "; Sleep(100);
			cout << "I   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "G   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "\n\n\n\t\t\t  ";
			return 0;
		}

		else
		{
			Sleep(360);
			cout << "\t\t\tIt's your birthday, you turned: " << count << "\n";;
			count++;
		}
	}


	for (double count = 39; count < 45 && count >= 39; count++)
	{
		if (dis10(gen) > 1 && dis10(gen) < 1163)
		{
			cout << "\n\n\n\t\t\tYou Died! Better luck next time!" << "\n\n\n\t\t\t";
			cout << "T   "; Sleep(100);
			cout << "H   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "K   "; Sleep(100);
			cout << "S   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "F   "; Sleep(100);
			cout << "O   "; Sleep(100);
			cout << "R   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "P   "; Sleep(100);
			cout << "L   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "Y   "; Sleep(100);
			cout << "I   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "G   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "\n\n\n\t\t\t  ";
			return 0;
		}

		else
		{
			Sleep(360);
			cout << "\t\t\tIt's your birthday, you turned: " << count << "\n";
			count++;
		}
	}


	for (double count = 44; count < 50 && count >= 44; count++)
	{
		if (dis11(gen) > 1 && dis11(gen) < 2574)
		{
			cout << "\n\n\n\t\t\tYou Died! Better luck next time!" << "\n\n\n\t\t\t";
			cout << "T   "; Sleep(100);
			cout << "H   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "K   "; Sleep(100);
			cout << "S   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "F   "; Sleep(100);
			cout << "O   "; Sleep(100);
			cout << "R   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "P   "; Sleep(100);
			cout << "L   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "Y   "; Sleep(100);
			cout << "I   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "G   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "\n\n\n\t\t\t  ";
			return 0;
		}

		else
		{
			Sleep(360);
			cout << "\t\t\tIt's your birthday, you turned: " << count << "\n";
			count++;
		}
	}


	for (double count = 49; count < 55 && count >= 49; count++)
	{
		if (dis12(gen) > 1 && dis12(gen) < 4430)
		{
			cout << "\n\n\n\t\t\tYou Died! Better luck next time!" << "\n\n\n\t\t\t";
			cout << "T   "; Sleep(100);
			cout << "H   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "K   "; Sleep(100);
			cout << "S   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "F   "; Sleep(100);
			cout << "O   "; Sleep(100);
			cout << "R   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "P   "; Sleep(100);
			cout << "L   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "Y   "; Sleep(100);
			cout << "I   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "G   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "\n\n\n\t\t\t  ";
			return 0;
		}

		else
		{
			Sleep(360);
			cout << "\t\t\tIt's your birthday, you turned: " << count << "\n";
			count++;
		}
	}


	for (double count = 54; count < 60 && count >= 54; count++)
	{
		if (dis13(gen) > 1 && dis13(gen) < 6638)
		{
			cout << "\n\n\n\t\t\tYou Died! Better luck next time!" << "\n\n\n\t\t\t";
			cout << "T   "; Sleep(100);
			cout << "H   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "K   "; Sleep(100);
			cout << "S   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "F   "; Sleep(100);
			cout << "O   "; Sleep(100);
			cout << "R   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "P   "; Sleep(100);
			cout << "L   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "Y   "; Sleep(100);
			cout << "I   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "G   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "\n\n\n\t\t\t  ";
			return 0;
		}

		else
		{
			Sleep(360);
			cout << "\t\t\tIt's your birthday, you turned: " << count << "\n";
			count++;
		}
	}


	for (double count = 59; count < 65 && count >= 59; count++)
	{
		if (dis14(gen) > 1 && dis14(gen) < 8926)
		{
			cout << "\n\n\n\t\t\tYou Died! Better luck next time!" << "\n\n\n\t\t\t";
			cout << "T   "; Sleep(100);
			cout << "H   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "K   "; Sleep(100);
			cout << "S   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "F   "; Sleep(100);
			cout << "O   "; Sleep(100);
			cout << "R   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "P   "; Sleep(100);
			cout << "L   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "Y   "; Sleep(100);
			cout << "I   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "G   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "\n\n\n\t\t\t  ";
			return 0;
		}

		else
		{
			Sleep(360);
			cout << "\t\t\tIt's your birthday, you turned: " << count << "\n";
			count++;
		}
	}


	for (double count = 64; count < 70 && count >= 64; count++)
	{
		if (dis15(gen) > 1 && dis15(gen) < 12118)
		{
			cout << "\n\n\n\t\t\tYou Died! Better luck next time!" << "\n\n\n\t\t\t";
			cout << "T   "; Sleep(100);
			cout << "H   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "K   "; Sleep(100);
			cout << "S   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "F   "; Sleep(100);
			cout << "O   "; Sleep(100);
			cout << "R   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "P   "; Sleep(100);
			cout << "L   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "Y   "; Sleep(100);
			cout << "I   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "G   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "\n\n\n\t\t\t  ";
			return 0;
		}

		else
		{
			Sleep(360);
			cout << "\t\t\tIt's your birthday, you turned: " << count << "\n";
			count++;
		}
	}



	for (double count = 69; count < 75 && count >= 69; count++)
	{
		if (dis16(gen) > 1 && dis16(gen) < 20886)
		{
			cout << "\n\n\n\t\t\tYou Died! Better luck next time!" << "\n\n\n\t\t\t";
			cout << "T   "; Sleep(100);
			cout << "H   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "K   "; Sleep(100);
			cout << "S   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "F   "; Sleep(100);
			cout << "O   "; Sleep(100);
			cout << "R   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "P   "; Sleep(100);
			cout << "L   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "Y   "; Sleep(100);
			cout << "I   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "G   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "\n\n\n\t\t\t  ";
			return 0;
		}

		else
		{
			Sleep(360);
			cout << "\t\t\tIt's your birthday, you turned: " << count << "\n";
			count++;
		}
	}


	for (double count = 74; count < 80 && count >= 74; count++)
	{
		if (dis17(gen) > 1 && dis17(gen) < 38723)
		{
			cout << "\n\n\n\t\t\tYou Died! Better luck next time!" << "\n\n\n\t\t\t";
			cout << "T   "; Sleep(100);
			cout << "H   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "K   "; Sleep(100);
			cout << "S   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "F   "; Sleep(100);
			cout << "O   "; Sleep(100);
			cout << "R   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "P   "; Sleep(100);
			cout << "L   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "Y   "; Sleep(100);
			cout << "I   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "G   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "\n\n\n\t\t\t  ";
			return 0;
		}

		else
		{
			Sleep(360);
			cout << "\t\t\tIt's your birthday, you turned: " << count << "\n";
			count++;
		}
	}


	for (double count = 79; count < 85 && count >= 79; count++)
	{
		if (dis18(gen) > 1 && dis18(gen))
		{
			cout << "\n\n\n\t\t\tYou Died! Better luck next time!" << "\n\n\n\t\t\t";
			cout << "T   "; Sleep(100);
			cout << "H   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "K   "; Sleep(100);
			cout << "S   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "F   "; Sleep(100);
			cout << "O   "; Sleep(100);
			cout << "R   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "P   "; Sleep(100);
			cout << "L   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "Y   "; Sleep(100);
			cout << "I   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "G   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "\n\n\n\t\t\t  ";
			return 0;
		}

		else
		{
			Sleep(360);
			cout << "\t\t\tIt's your birthday, you turned: " << count << "\n";
			count++;
		}
	}


	for (double count = 84; count < 102 && count >= 101; count++)
	{
		if (dis19(gen) > 1 && dis19(gen) < 201978)
		{
			cout << "\n\n\n\t\t\tYou Died! Better luck next time!" << "\n\n\n\t\t\t";
			cout << "T   "; Sleep(100);
			cout << "H   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "K   "; Sleep(100);
			cout << "S   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "F   "; Sleep(100);
			cout << "O   "; Sleep(100);
			cout << "R   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "P   "; Sleep(100);
			cout << "L   "; Sleep(100);
			cout << "A   "; Sleep(100);
			cout << "Y   "; Sleep(100);
			cout << "I   "; Sleep(100);
			cout << "N   "; Sleep(100);
			cout << "G   "; Sleep(100);
			cout << "    "; Sleep(100);
			cout << "\n\n\n\t\t\t  ";
			return 0;
		}

		else
		{
			Sleep(360);
			cout << "\t\t\tIt's your birthday, you turned: " << count << "\n";
			count++;
		}
	}




	}





