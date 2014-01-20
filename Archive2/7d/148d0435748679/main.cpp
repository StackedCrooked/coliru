// getlineFun.cpp : Defines the entry point for the console application.
//


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
// extract to string

struct Transaction
{
    int Item;
	float prob;
	Transaction *next;
};

#define ItemNum 1000
Transaction *Trans[ItemNum]; //Adjacency list stors list of Items in each Transactions.


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
		i = 0;
		int m = 0;
		while (!inFile.eof())
		{
			FollowingItem = NULL;

		    getline(inFile, line);


			while (i<3)
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
			while (r < 3)
			{
				cout << Trans[i]->Item << " " << Trans[i]->prob<<" ";
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

	while ((Trans[i]->Item >> a >> b) && (Trans[i] != NULL))
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


