/*
Program: CSCI PROJECT 4 (HANGMAN)
Author: YEOH YAN CHUN
Class: FRIDAY
Date: 12/5/2014
Description:

THIS IS A HANGMAN GAME PROGRAM WHERE PLAYERS ARE REQUIRED TO GUESS THE LETTERS IN AN UNKNOWN WORD.

I certify that the code below is my own work.

Exception(s): N/A

*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

const int MAX_NUMS = 200;
const int MAX_GUESSES = 8;
const string LETTERS = "abcdefghijklmnopqrstuvwxyz";

char inputLetter();
int findChar(char letter, string word);
string getGuessedWord(string secretWord, string lettersGuessed), wordGuessed;
void printSpace(string wordGuessed);

int main()
{
    string oneWord;
	string secretWord;
	string words[MAX_NUMS];
	string lettersGuessed;
	string alreadyGuessed;
	char letter;
	int randomValue, incorrectGuesses = 0, availableGuess = 8;
	int count = 0, gCount, chances = 8, i = 8;

	ifstream myFile;
	myFile.open("P4Words.txt");

	cout << "Loading word list from file ..." << endl;

	if (!myFile)
	{
		cout << "Error: Unable to open file for input" << endl;
		return 0;
	}

	myFile >> oneWord;

	while (!myFile.eof())
	{
		words[count] = oneWord;
		count++;

		myFile >> oneWord;
	}

	cout << count + 1 << " words loaded." << endl;

	srand(static_cast<unsigned int>(time(0)));
	randomValue = rand() % count;
	secretWord = words[randomValue];

	cout << "THE SECRET WORD IS " << secretWord;
	cout << "Welcome to the game, Hangman by Yeoh Yan Chun !" << endl;
	cout << "I am thinking of a word that is " << secretWord.length() << " letters long." << endl;
	cout << "-----------------------------------------------" << endl;


	while (i != 0)
	{
		
		if (getGuessedWord(secretWord, lettersGuessed) == secretWord)
		{
			cout << "Congratulaions, you won !";
			return 0;
		}

		cout << "You have " << chances << " guesses left." << endl;
		cout << "Letters guessed so far: " << lettersGuessed << endl;
		letter = inputLetter();

		

		for (int j = 0; j < lettersGuessed.length(); j++)
		{
			while (letter == lettersGuessed[j])
			{
				cout << "Oops! You've already guessed that letter: ";
				printSpace(wordGuessed);
				cout << endl;
				cout << "-----------------------------------------------" << endl;

				chances = chances - 1;

				if (chances == 0)
				{
					cout << "Sorry, you ran out of guesses. The word was " << secretWord << "." << endl;
					return 0;
				}

				cout << "You have " << chances << " guesses left." << endl;
				cout << "Letters guessed so far: " << lettersGuessed << endl;
				letter = inputLetter();


			}
		}

		lettersGuessed += letter;

		wordGuessed = getGuessedWord(secretWord, lettersGuessed);

		if (findChar(letter, secretWord) == -1)
		{	
			chances = chances - 1;

			if (chances == 0)
			{
				cout << "-----------------------------------------------" << endl;
				cout << "Sorry, you ran out of guesses. The word was " << secretWord << "." << endl;
				return 0;
			}

			cout << "Oops ! That letter is not in my word ";
			printSpace(wordGuessed);
			cout << endl;
			cout << "-----------------------------------------------" << endl;
		}
		else
		{
			cout << "Good guess: ";
			wordGuessed = getGuessedWord(secretWord, lettersGuessed);
			printSpace(wordGuessed);
			cout << endl;
			cout << "-----------------------------------------------" << endl;
		}
	}

	return 0;
}

char   inputLetter()
{
	int i = 0;
	char letter;

	do
	{
		cout << "Please guess a letter: ";
		cin >> letter;

		for (i = 0; i < 25; i++)
		{
			if (letter == LETTERS[i])
			{
				return letter;
			}
		}

		if (letter != LETTERS[i])
		{
			cout << "Oops! That is an invalid character." << endl;
		}
	} while (letter != LETTERS[i]);

}

int findChar(char letter, string word)
{
	int found = -1, i = 0;

	while ((found == -1) && (i < word.length()))
	{
		if (letter == word[i])
			found = i;

		else
			i++;
	}

	return found;
}

string getGuessedWord(string secretWord, string lettersGuessed)
{
	string wordGuessed = secretWord , wordsI, wordsII ;

	// wordsI - to store altered string
	// wordsII - to store the altered string for comparison with new altered string (wordsII)
	for (int k = 0; k < secretWord.length(); k++)
	{
		wordGuessed[k] = '_';
	}

	for (int i = 0; i < lettersGuessed.length(); i++)
	{
		for (int j = 0; j < secretWord.length(); j++)
		{
			if ((lettersGuessed[i] == secretWord[j]) && (wordGuessed != " "))
				wordGuessed[j] = lettersGuessed[i];
			//else if (wordGuessed[j] == '_')
				//cout << "_";
		}
	}	
	
	return wordGuessed;
}

void printSpace(string wordGuessed)
{
	for (int i = 0; i < wordGuessed.length(); i++)
	{
		cout << wordGuessed[i];
		cout << " ";
	}
}
