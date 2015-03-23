#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
using namespace std;


const int RDC1 = 8;  //region detail column 1
const int RDC2 = 16;  //region detail column 2
const int RDC3 = 4;  //region detail column 3
const int RDC4 = 18;  //region detail column 4

const int MONTHS = 12;

const int LOANYEARS10 = 30;
const int LOANYEARS20 = 15;
const int LOANYEARS30 = 5;
const int LOANYEARS40 = 2;

const double LOANINTERESTRATE10 = 0.041;
const double LOANINTERESTRATE20 = 0.032;
const double LOANINTERESTRATE30 = 0.045;
const double LOANINTERESTRATE40 = 0.065;
const int MAXIMUMLOAN10 = 425000;
const int MAXIMUMLOAN20 = 425000;
const int MAXIMUMLOAN30 = 100000;
const int MAXIMUMLOAN40 = 25000;

const int MINIMUMLOAN10 = 5000;
const int MINIMUMLOAN20 = 5000;
const int MINIMUMLOAN30 = 5000;
const int MINIMUMLOAN40 = 500;

const char MENU_VALUE1 = 'U';
const char MENU_VALUE2 = 'R';
const char MENU_VALUE3 = 'E';
const char MENU_VALUE4 = 'S';
const char MENU_VALUE5 = 'L';
const char MENU_VALUE6 = 'C';
const char MENU_VALUE7 = 'Q';



/********************************************************************************

Function prototypes for Project #3

********************************************************************************/

char displayMenu();

void uploadFile(bool &loadSuccess, vector<string> &reg, vector<string> &eID,
    vector<string> &lID, vector<int> &lCode, vector<int> &amt,
	vector<int> &y, vector<int> &m, vector<int> &d, vector<int> &pmtCount);


void displayRegionDetails(int fileCount, const vector<string> &reg, const vector<string> &lID,
	const vector<string> &lCode, const vector<int> &amt,
	vector<int> &y, vector<int> &m, vector<int> &d);

void displayEmployeeDetails(int fileCount, const vector<string> &eID,
	const vector<string> &lID, const vector<string> &lCode,
	const vector<int> &amt, const vector<int> pmtCount);

void displayAllSummary(int fileCount, const vector<string> &lCode,
	const vector<int> &amt, const vector<int> pmtCount);

double computeR(double interestRate, int loanAmount,
	int paymentsPerYear, int lengthOfLoanInYears);

double computeLprime(double R, double interestRate, int paymentsPerYear,
	int lengthOfLoanInYears, int paymentsReceived);


void clearAllVectors(int &fileCount, vector<string> &reg, vector<string> &eID,
	vector<string> &lID, vector<string> &lCode, vector<int> &amt,
	vector<int> &y, vector<int> &m, vector<int> &d, vector<int> &pmtCount);

void listEmployeeIDs(int fileCount, const vector<string> &eID);








int main(int argc, const char * argv[])
{

	char userChoice = '?';


	vector<string> region;
	vector<string> employeeID;
	vector<string> loanID;
	vector<int> loanCode;
	vector<int> loanAmount;
	vector<int> originationYear;
	vector<int> originationMonth;
	vector<int> originationDay;
	vector<int> numberOfPaymentsMade;
	vector<string> lastName;
	vector<string> firstName;
	vector<string> address;

	bool allOK = false;

	cout << "Welcome to the loan monitoring system." << endl
		<< "This displays information for both open and closed loans." << endl << endl;

	while (userChoice != 'q' && userChoice != 'Q')
	{
		userChoice = displayMenu();

		switch (userChoice)
		{
		case 'U':
		case 'u':
			cout << "the user asked you to do: " << userChoice << endl;
			uploadFile(allOK, region, employeeID, loanID, loanCode, loanAmount, originationYear, originationMonth, originationDay, numberOfPaymentsMade);
			break;

		case 'R':
		case 'r':
			break;

		case 'E':
		case 'e':
			break;

		case 'S':
		case 's':
			break;

		case 'L':
		case 'l':
			break;

		case 'C':
		case 'c':
			break;

		case 'Q':
		case 'q':
			cin.get();
			return 0;
			break;

		default:
			cout << "You entered: " << userChoice << endl;
			cout << "Please check the valid menu options and re-run the program." << endl;
		}

    }
	cin.get();
	return 0;
}






/********************************************************************************

Implementation code provide for selected functions for Project #3

********************************************************************************/


char displayMenu()
{
	char whatToDo = '?';
	bool selectionValid = false;
	int attemptCount = 0;

	do
	{
		attemptCount++;

		cout << "Upload a regional loan data file \t U" << endl;
		cout << "display details for Region \t R" << endl;
		cout << "display details for employee ID \t E" << endl;
		cout << "display Summary (all loaned files) \t S" << endl;
		cout << "List employee id's loaned \t L" << endl;
		cout << "Clear all vectors \t C" << endl;
		cout << "Quit \t Q" << endl;

		if (attemptCount > 1)
		{
			cout << endl << "Your previous selection was not a valid option...";
		}

		cout << endl << "Please enter your choice: ";
		char whatToDo = '?';
		cin >> whatToDo;
		cin.ignore(500, '\n');

		bool selectionValid = false;

		if (toupper(whatToDo) == toupper(MENU_VALUE1))
			selectionValid = true;
		else if (toupper(whatToDo) == toupper(MENU_VALUE2))
			selectionValid = true;
		else if (toupper(whatToDo) == toupper(MENU_VALUE3))
			selectionValid = true;
		else if (toupper(whatToDo) == toupper(MENU_VALUE4))
			selectionValid = true;
		else if (toupper(whatToDo) == toupper(MENU_VALUE5))
			selectionValid = true;
		else if (toupper(whatToDo) == toupper(MENU_VALUE6))
			selectionValid = true;
		else if (toupper(whatToDo) == toupper(MENU_VALUE7))
			selectionValid = true;
		else
			selectionValid = false;
		
	} while (!selectionValue);

	return whatToDo;

}


void uploadFile(bool &loadSuccess, vector<string> &reg, vector<string> &eID,
	vector<string> &lID, vector<int> &lCode, vector<int> &amt,
	vector<int> &y, vector<int> &m, vector<int> &d, vector<int> &pmtCount)
{
	cout << "entering function uploadFile." << endl;

	int todaysYear = 0, todaysMonth = 0, todaysDay = 0;
	char ch = '?';

	int onLine = 0;

	string inputFileName = "";

	ifstream inputFile;

	cout << "Please enter the full path and name of the input data file: ";
	getline(cin, inputFileName);
	inputFile.open((inputFileName.c_str())));

	int numberOfOpen = 0;

	int loanCode;
	int loanYears;
	double loanInterestRate;
	int maximumLoan;
	int minimumLoan;
	double loanAmount;

	double one = 1.000000;

	int goodLines = 0;
	int badLines = 0;

	int originationYear;
	int originationMonth;
	int originationDay;

	int numberOfPaymentsMade;

	string region;
	string employeeID;
	string loanID;
	string lastName;
	string firstName;
	string address;

	long double interestOverMonths = 0.00;
	double monthlyPayment = 0.00;
	double principalPaid = 0.00;
	double unpaidPrincipal = 0.00;
	double onePlusInterestOverMonths = 0.00;
	double monthsTimesLoanYears = 0.00;
	double monthsTimesLoanYearsMinusPaymentsMade = 0.00;
	double unpaidPrincipalPower = 0.00;

	int numberOfLoansOpen = 0;
	int numberOfLoansClosed = 0;

	double loanTotalAmtOpen = 0.00;
	double loanTotalAmtClosed = 0.00;

	long double totalPrincipalPaidClosed = 0.00;
	long double totalUnpaidPrincipalClosed = 0.00;

	long double totalPrincipalPaidOpen = 0.00;
	long double totalUnpaidPrincipalOpen = 0.00;

	int line0 = 0;
	string line1 = "";
	string line2 = "";

	int total = 0;

	if (!inputFile)
	{
		cout << "The input data file failed to open." << endl
			<< "Check to ensure that the file: " << inputFileName << " is a valid file" << endl;

		cin.get();
	}
	else
	{
		cout << endl << "The file: " << inputFileName << " opened successfully!" << endl << endl;

		inputFile >> todaysYear >> ch >> todaysMonth >> ch >> todaysDay;

		onLine = 0;		//0

		getline(inputFile, line1);			//skips the remainder of the first line with the date on it
		getline(inputFile, line2);			//skips the entire second line with the headings


		onLine = onLine + 1;	//1

		while (inputFile >> region >> employeeID >> loanID >> loanCode >> loanAmount
			>> originationYear >> ch >> originationMonth >> ch >> originationDay
			>> numberOfPaymentsMade >> lastName >> firstName && getline(inputFile, address))
		{


			/*cout << employeeID << " ";
			cout << loanID << " ";
			cout << loanType << " ";
			cout << loanAmount << " ";
			cout << originationYear << " ";
			cout << originationMonth << " ";
			cout << originationDay << " ";
			cout << numberOfPaymentsMade << " ";
			cout << lastName << " ";
			cout << firstName << " ";
			cout << address << endl;
			*/

			onLine = onLine + 1;

			string errorsOfFailedTests;

			string originationDateTest = "\n\tInvalid origination date: ";

			string loanAmountTest = "\n\tThe loan amount is outside limits.";
			string numberOfPaymentsMadeTest = "\n\tThe number of payments received is not valid.";
			string loanTypeTest = "\n\tInvalid BRSL Code.";


			switch (loanCode)
			{
			case 10: loanYears = LOANYEARS10, loanInterestRate = LOANINTERESTRATE10, maximumLoan = MAXIMUMLOAN10, minimumLoan = MINIMUMLOAN10;
				break;
			case 20: loanYears = LOANYEARS20, loanInterestRate = LOANINTERESTRATE20, maximumLoan = MAXIMUMLOAN20, minimumLoan = MINIMUMLOAN20;
				break;
			case 30: loanYears = LOANYEARS30, loanInterestRate = LOANINTERESTRATE30, maximumLoan = MAXIMUMLOAN30, minimumLoan = MINIMUMLOAN30;
				break;
			case 40: loanYears = LOANYEARS40, loanInterestRate = LOANINTERESTRATE40, maximumLoan = MAXIMUMLOAN40, minimumLoan = MINIMUMLOAN40;
				break;
			default: errorsOfFailedTests = loanTypeTest;
			}

			/*cout << "The interest rate of the loan is: " << loanInterestRate << endl;

			cout << "The number of lines read is: " << onLine << endl;
			*/

			if (loanAmount < minimumLoan)
			{
				errorsOfFailedTests = errorsOfFailedTests + loanAmountTest;
			}
			if (loanAmount > maximumLoan)
			{
				errorsOfFailedTests = errorsOfFailedTests + loanAmountTest;
			}

			if (numberOfPaymentsMade < 0)
			{
				errorsOfFailedTests = errorsOfFailedTests + numberOfPaymentsMadeTest;
			}

			if (originationYear > todaysYear)
			{
				errorsOfFailedTests = errorsOfFailedTests + originationDateTest;
			}
			else if ((originationMonth > 12) || (originationMonth < 1))
			{
				errorsOfFailedTests = errorsOfFailedTests + originationDateTest;
			}
			else if ((originationDay > 30) || (originationDay < 1))
			{
				errorsOfFailedTests = errorsOfFailedTests + originationDateTest;
			}
			else if ((originationYear == todaysYear))
			{
				if (originationMonth > todaysMonth)
				{
					errorsOfFailedTests = errorsOfFailedTests + originationDateTest;
				}
				if (originationMonth == todaysMonth)
				{
					if (originationDay > todaysDay)
					{
						errorsOfFailedTests = errorsOfFailedTests + originationDateTest;
					}
				}
			}


			int stringSize = errorsOfFailedTests.length();	//supplemental text p961

			if (stringSize != 0)
			{
				badLines = badLines + 1;
				cout << endl << employeeID << " " << loanID << " " << loanCode << " "
					<< fixed << setprecision(2) << loanAmount << " " << numberOfPaymentsMade << endl;

				cout << errorsOfFailedTests;

				if (errorsOfFailedTests.find(originationDateTest) != string::npos)	//found in the supplemental text to find strings p965
				{
					cout << originationYear << "/" << originationMonth << "/" << originationDay << endl;
				}
				else
				{
					cout << endl;
				}

				//cout << "the number of bad lines are " << badLines << endl; 
			}

}



void displayRegionDetails(int fileCount, const vector<string> &reg, const vector<string> &lID,
const vector<string> &lCode, const vector<int> &amt,
vector<int> &y, vector<int> &m, vector<int> &d)
{
	/*
	*  NOTE: This function is provided for COSC 051, Spring 2015 projects,
	*  it may be used in total or in part without attribution (WAW)
	*
	*  This function displays details about loans for a specific region
	*  The user is prompted to enter the region to display
	*
	*  A few global constants are used to control the width of output:
	*
	*       const int RDC1 =  8;  //region detail column 1
	*       const int RDC2 = 16;  //region detail column 2
	*       const int RDC3 =  4;  //region detail column 3
	*       const int RDC4 = 18;  //region detail column 4
	*
	*  Either add these to your global constants, or replace them in the code
	*  below with your own constants (do not use magic numbers!).
	*
	*/

	cout << "Entered function displayRegionDetails" << endl;

	string regionToDisplay = "";  //store value of region that user requested to display
	long totalAmount = 0;         //tally variable to keep total of all loans for requested region

	if (fileCount <= 0)
	{
		//no data files have been loaded
		cout << "No files have been loaded, nothing to display...\n";
	}
	else
	{
		//prompt for and store region to display
		cout << "Enter name of region to display (North, South, East, or West): \n";
		getline(cin, regionToDisplay);

		//NOTE: assume that the entry was one of the correct region values with correct 
		//      capitalization, no data validation is required

		cout << "Details information of loans from " << regionToDisplay << " region:\n";

		//search vectors for data matching requested region
		for (int i = 0; i < reg.size(); i++)
		{
			//if the region matches the user entry, then output values from parallel vectors
			//and update the tally variable
			if (reg.at(i) == regionToDisplay)
			{
				cout << setw(RDC1) << reg.at(i);
				cout << setw(RDC2) << lID.at(i);
				cout << "  " << setfill('0');
				cout << setw(4) << y.at(i) << "/";
				cout << setw(2) << m.at(i) << "/";
				cout << setw(2) << d.at(i) << "  ";
				cout << setfill(' ');
				cout << setw(RDC3) << lCode.at(i);
				cout << setw(RDC4) << amt.at(i);
				cout << endl;
				totalAmount += amt.at(i);
			}
		}

		//output a line to separate the data details from the total
		for (int u = 0; u < (RDC1 + RDC2 + RDC3 + RDC4 + 20); u++)
		{
			cout << "-";
		}
		cout << endl;

		//output the total
		cout << setw(RDC1 + 14) << "  Total:" << setw(RDC2 + RDC3 + RDC4) << totalAmount << endl;
	}

	cout << "Exiting function displayRegionDetails" << endl;

} //END function displayRegionDetails



double computeR(double interestRate, int loanAmount, int paymentsPerYear, int lengthOfLoanInYears)
{
	/*
	*  NOTE: This function stub is provided as an example
	*  for COSC 051, Spring 2015 projects.
	*
	*  Use this during early milestones, and then add your
	*  implementation code when ready.
	*
	*/

	double R = -1.0;  //initialized to an invalid value

	cout << "Entered function computeR" << endl;

	//implementation code goes here

	cout << "Exiting function computeR" << endl;

	return R;

} //END function computeR



double computeLprime(double R, double interestRate, int paymentsPerYear, int lengthOfLoanInYears, int paymentsReceived)
{
	/*
	*  NOTE: This function is provided for COSC 051, Spring 2015 projects,
	*  it may be used in total or in part without attribution (WAW)
	*
	*  This function computes the value of L-prime
	*
	*/

	cout << "Entered function computeLprime" << endl; //output for testing and development

	double interestRateI = interestRate / paymentsPerYear;

	//calculate L'
	double LprimeExp = (-1 * ((paymentsPerYear * lengthOfLoanInYears) - paymentsReceived));
	double LprimeNumerator = (1 - (pow((1 + interestRateI), LprimeExp)));
	double Lprime = R * (LprimeNumerator / interestRateI);

	cout << "Exiting function computeLprime" << endl; //output for testing and development

	return Lprime;

} //END function computeLprime



void clearAllVectors(int &fileCount, vector<string> &reg, vector<string> &eID,
	vector<string> &lID, vector<string> &lCode, vector<int> &amt,
	vector<int> &y, vector<int> &m, vector<int> &d, vector<int> &pmtCount)
{
	/*
	*  NOTE: This function is provided for COSC 051, Spring 2015 projects,
	*  it may be used in total or in part without attribution (WAW)
	*
	*  This function removes all data from the parallel vectors
	*
	*/

	cout << "Entered function clearAllVectors\n";

	int resultOfClear = reg.size();
	cout << "Vectors currently contain " << reg.size() << " records.\n";

	reg.clear();
	eID.clear();
	lID.clear();
	lCode.clear();
	amt.clear();
	y.clear();
	m.clear();
	d.clear();
	pmtCount.clear();

	resultOfClear = reg.size() + eID.size() + lID.size() + lCode.size() + amt.size() +
		y.size() + m.size() + d.size() + pmtCount.size();


	fileCount = 0;

	if (resultOfClear != 0)
	{
		cout << "NOTE: Something went wrong in the clearAllVectors function.\n";
		cout << "      It appears that one or more vectors still have contents.\n";
		cout << "      Please quit and reload data before running any reports.\n";
	}
	else
	{
		cout << "Vectors have been emptied of contents.\n";
	}

	cout << "Exiting function clearAllVectors\n";

} //END function clearAllVectors


void listEmployeeIDs(int fileCount, const vector<string> &eID)
{
	/*
	*  NOTE: This function is provided for COSC 051, Spring 2015 projects,
	*  it may be used in total or in part without attribution (WAW)
	*
	*  This function finds and displays a list of all unique employee IDs
	*  for data that are loaded in the vectors
	*
	*/

	cout << "Entered function listEmployeeIDs\n";

	cout << "Checking " << eID.size() << " records for unique employee IDs" << endl;

	if (fileCount > 0)
	{
		vector<string> uniqueIDs;
		bool duplicateID = false;

		//evaluate each employee ID in the eID vector
		for (int a = 0; a < eID.size(); a++)
		{
			duplicateID = false;
			//compare the current employee ID to each ID in the local vector
			for (int b = 0; b < uniqueIDs.size(); b++)
			{
				if (uniqueIDs.at(b) == eID.at(a))
				{
					//this ID has already been loaded into the local vector
					duplicateID = true;
				}

			} //END inner for loop to determine if current ID is already in local vector

			if (duplicateID)
			{
				//do nothing
			}
			else
			{
				//add this employee ID to the local vector
				uniqueIDs.push_back(eID.at(a));
			}
			
		} //END outer for loop

		cout << "List of " << uniqueIDs.size() << " employee IDs that have been loaded:\n";

		for (int u = 0; u < uniqueIDs.size(); u++)
		{
			cout << uniqueIDs.at(u) << endl;
		}
		cout << endl;

	} //END if (fileCount > 0)

	else
	{
		cout << "No files have been loaded, nothing to display...\n";

	} //END else block paired with if (fileCoount > 0) 

	cout << "Exiting function listEmployeeIDs\n";

} //END function listEmployeeIDs


/*{
	do
	{
		cout << "Upload a regional loan data file \t U" << endl;
		cout << "display details for Region \t R" << endl;
		cout << "display details for employee ID \t E" << endl;
		cout << "display Summary (all loaned files) \t S" << endl;
		cout << "List employee id's loaned \t L" << endl;
		cout << "Clear all vectors \t C" << endl;
		cout << "Quit \t Q" << endl;

		cout << "Please enter your choice: ";
		cin >> choice;

	} while ((choice != 'q') || (choice != 'Q'));

	if (choice == 'u' || choice == 'U')
	{

	}

	if (choice == 'r' || choice == 'R')
	{

	}

	if (choice == 'e' || choice == 'E')
	{

	}

	if (choice == 's' || choice == 'S')
	{

	}

	if (choice == 'l' || choice == 'L')
	{

	}

	if (choice == 'c' || choice == 'c')
	{

	}

	if ((choice == 'q') || (choice == 'Q'))
	{
		cout << "The program will quit now" << endl;
		cin.get();
		return 0;
	}
}
*/