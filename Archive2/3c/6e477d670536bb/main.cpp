// getlineFun.cpp : Defines the entry point for the console application.
//

/* DataBae in text file like:(intger number float number......intger number float number)
where the float number is: the prob. of previous intger number
each line has diffr. length
ex:
1 0.933 2 0.865 3 0.919 
10 0.854 25 0.906 26 0.726 
38 0.882 39 0.853 
*/


#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include "stdafx.h"
#include <iostream> 
#include <fstream>
#include <strstream>
#include <sstream>
#include <utility>
#include <map>
#include <ctime> 
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<time.h>



using namespace std;


struct Transaction
{
    int Item;
	float prob;
	Transaction *next;
};

#define ItemNum 1000
Transaction *Trans[ItemNum]; //array of linked list to stor the list of Items in each /row.


int expectedK;			/* User input upper limit of itemset size to be mined */
int realK;			/* Actual upper limit of itemset size can be mined */
int threshold;			/* User input support threshold */
int numItem;			/* Number of items in the database */
int numTrans;			/* Number of transactions in the database */
char dataFile[100];		/* File name of the database */
char outFile[100];		/* File name to store the result of mining */

void pass1()
{
	
	
	Transaction *NewItem, *FollowingItem;
	int  i, j;
    i=0;
	int transSize;
	NewItem = new Transaction;
	for (int a = 0; a <= ItemNum - 1; a++)
		Trans[a] = NULL;

	ifstream inFile;
	inFile.open(dataFile);


	if (inFile.fail())
        cout << "\n The file has been not found, please try again \n " ;
	else
	{
		string line;
		cout << "\n File found!\nReading the file data! \n";

		// Read the file until EOF
		
		while (!inFile.eof()) // the goal of this loop is to scan line/row by scan line/row
		{
			FollowingItem = NULL;

		    getline(inFile, line);  


			while (i<3) // I put 3 because I don’t know how to calculate the size of each row?? I need help in this loop
                        // the goal of this loop is scan item by item in each row, for ex, when this loop finsh reading first line, I want to got:
                        // Trans[0]= 1 0.933 2 0.865 3 0.919 
                        // when this loop finsh reading second line, I want to got:Trans[1]=10 0.854 25 0.906 26 0.726
                        // etc until the end of file

			{

				NewItem = new Transaction;
				inFile >> NewItem->Item >> NewItem->prob;
				NewItem->next = NULL;

				if (Trans[i] == NULL)
					Trans[i] = FollowingItem = NewItem;

				else
				{
					FollowingItem->next = NewItem;
					FollowingItem = NewItem;
				}
				i++;
			}
		
		}

	}
	inFile.close();
		//print  
		i = 0;
		int r = 0;
		while (Trans[i] != NULL)
		{
			while (r < 3) //I put 3 because I don’t know how to calculate the size of each row?? I need help in this loop
			{
				cout << Trans[i]->Item << " " << Trans[i]->prob<<" "; // when it print, it skip the first line!, i don't know why!
				Trans[i] = Trans[i]->next;
				r += 1;

			}
			cout << "\n";
			i++;
		}
	
	return;
}
//*********************************************************************************************
void Pair_count()
{
	std::map<std::pair<int, int>, int> pairToCount;
	int i = 0;
	int a = 0, b = 0;
// here I have problem, Trans become empty = null !, I don't know why! so it gives me error
	while ((Trans[i]->Item >> a >> b) && (Trans[i] != NULL)) /* I want from this loop count the pair in the arary of linked list Trans[i]
                                                              Trans[0]= 1 0.933 2 0.865 3 0.919 
                                                              Trans[1]= 2 0.854 1 0.906 26 0.726 
                                                              Trans[2]= 38 0.882 39 0.853 
                                                              
                                                              such that:
                                                              fitst it create pair like
                                                              (1,2)
                                                              (1,3)
                                                              (2,3)
                                                              (2,1)
                                                              (2,26)
                                                              (1,26)
                                                              (38,39)
                                                              
                                                              then it count them
                                                              (1,2)=2 (the count is 2 because we have (2,1) in  Trans[1])
                                                              (1,3)=1
                                                              (2,3)=1
                                                              (2,1)=2  (the count is 2 because we have (1,2) in  Trans[0])
                                                              (2,26)=1
                                                              (1,26)=1
                                                              (38,39)=1
                                                              
                                                              */
	{
		auto it = pairToCount.find(std::make_pair(b, a));

		++pairToCount[
			(it != pairToCount.end()) ? std::make_pair(b, a)
				: std::make_pair(a, b)];
			Trans[i] = Trans[i]->next;
			i++;

	}

	for (const auto& p : pairToCount)
	{
		std::cout << "(" << p.first.first << " " << p.first.second << ") = "
			<< p.second << '\n';
	}


}
/******************************************************************************************
InputFile Function: Read the input parameters from the configuration file.
/*******************************************************************************************/

void InputFile(char *configFile)
{
	FILE *fp;
	float thresholdDecimal;
	configFile = "InputFile.txt";


	if ((fp = fopen(configFile, "r")) == NULL) {
		cout << "Can't open InputFile.txt" << configFile << "\n";
		exit(1);
	}

	fscanf(fp, "%d %f %d %d", &expectedK, &thresholdDecimal, &numItem, &numTrans);
	fscanf(fp, "%s %s", dataFile, outFile);
	fclose(fp);

	cout << "===========================================================\n";
	cout << "                      Input File                           \n";
	cout << "===========================================================\n";

	cout << "\n User specified maximum size of itemset to be mined = " << expectedK;
	cout << "\n  Normalized support threshold, range: (0, 1] = " << thresholdDecimal;
	cout << "\n  Total number of different items in the DB = " << numItem;
	cout << "\n Total number of transactions in the DB = " << numTrans;
	cout << "\n Data File Name = " << dataFile;
	cout << "\n Result file for storing the large itemsets = " << outFile << "\n\n";

	threshold = thresholdDecimal * numTrans;
	if (threshold == 0)
		threshold = 1;
	cout << "\n\n Threshold = " << threshold;

}


//**********************************************
void main(int argc, char *argv[])
{

	system("cls");

	int headerTableSize;
	float time1, time2, time3;


	if (argc != 1)
	{
		cout << "Usage: %s <InputFile.txt>\n\n" << argv[0];
		cout << "Content of InputFile.txt:\n";

		exit(1);
	}

	//read input parameters 

	InputFile(argv[1]);


	int c = 0;
	cout << "1- code 1  \n";
	cout << "2- code \n";
	cout << "3- Quit \n";


	do
	{
		cout << "\n\n Please Enter your choice = ";
		cin >> c;
		system("cls");
		switch (c)
		{
		case 1:
			pass1();

            Pair_count();

			
			cout << "\n\n";
			system("PAUSE");
			break;

		case 2:
		//
        //
			cout << "\n\n";
			system("PAUSE");
			break;

		case 3:
			cout << "\n Bye..... \n";
			exit(0);
			break;

		default:
			cout << "\n Invalid selection \n";

		}
	} while ((c > 0) && (c <= 3));






	system("PAUSE");
	return;
}


