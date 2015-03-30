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

const int MAX_MENU_ATTEMPTS = 500;

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
	const vector<int> &lCode, const vector<int> &amt,
	vector<int> &y, vector<int> &m, vector<int> &d);

void displayEmployeeDetails(int fileCount, const vector<string> &eID,
	const vector<string> &lID, const vector<int> &lCode,
	const vector<int> &amt, const vector<int> pmtCount);

void displayAllSummary(int fileCount, const vector<int> &lCode,
	const vector<int> &amt, const vector<int> pmtCount);

double computeR(double interestRate, int loanAmount,
	int paymentsPerYear, int lengthOfLoanInYears);

double computeLprime(double R, double interestRate, int paymentsPerYear,
	int lengthOfLoanInYears, int paymentsReceived);


void clearAllVectors(int &fileCount, vector<string> &reg, vector<string> &eID,
	vector<string> &lID, vector<int> &lCode, vector<int> &amt,
	vector<int> &y, vector<int> &m, vector<int> &d, vector<int> &pmtCount);

void listEmployeeIDs(int fileCount, const vector<string> &eID);


int main(int argc, const char * argv[])
{

	char userChoice = '?';
	int countFilesLoaded = 0;

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

	bool fileLoadOK = false;

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

			fileLoadOK = false;

			uploadFile(fileLoadOK, region, employeeID, loanID, loanCode, loanAmount, originationYear, originationMonth, originationDay, numberOfPaymentsMade);

			if (fileLoadOK)
			{
				countFilesLoaded++;
			}

			break;

		case 'R':
		case 'r':
			cout << "the user asked you to do: " << userChoice << endl;

			displayRegionDetails(countFilesLoaded, region, loanID, loanCode, loanAmount, originationYear, originationMonth, originationDay);

			break;

		case 'E':
		case 'e':
			cout << "the user asked you to do: " << userChoice << endl;

			displayEmployeeDetails(countFilesLoaded, employeeID, loanID, loanCode, loanAmount, numberOfPaymentsMade);

			break;

		case 'S':
		case 's':
			cout << "the user asked you to do: " << userChoice << endl;

			displayAllSummary(countFilesLoaded, loanCode, loanAmount, numberOfPaymentsMade);

			break;

		case 'L':
		case 'l':
			cout << "the user asked you to do: " << userChoice << endl;

			listEmployeeIDs(countFilesLoaded, employeeID);

			break;

		case 'C':
		case 'c':
			cout << "the user asked you to do: " << userChoice << endl;

			clearAllVectors(countFilesLoaded, region, employeeID, loanID, loanCode, loanAmount, 
				originationYear, originationMonth, originationDay, numberOfPaymentsMade);

			break;

		case 'Q':
		case 'q':
			cout << "The program will quit now." << endl;
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

		cout << endl << endl << endl;
		cout << setw(45) << "Upload a regional loan data file \t U" << endl;
		cout << setw(45) << "display details for Region \t R" << endl;
		cout << setw(45) << "display details for employee ID \t E" << endl;
		cout << setw(45) << "display Summary (all loaded files) \t S" << endl;
		cout << setw(45) << "List employee id's loaded \t L" << endl;
		cout << setw(45) << "Clear all vectors \t C" << endl;
		cout << setw(45) << "Quit \t Q" << endl;
		cout << endl;

		if (attemptCount > 1)
		{
			cout << endl << "Your previous selection was not a valid option...";
		}

		cout << endl << "Please enter your choice: ";
		cin >> whatToDo;
		cin.ignore(500, '\n');

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
		
	} while (!selectionValid && attemptCount < MAX_MENU_ATTEMPTS);

	cout << "exiting function displayMenu, return value is " << whatToDo << endl;

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

	int startSize = reg.size();
	int endSize = reg.size();

	loadSuccess = false;

	//inputting the file
	ifstream inputFile;

	cout << "Please enter the full path and name of the input data file: ";
	getline(cin, inputFileName);
	inputFile.open(inputFileName.c_str());

	int numberOfOpen = 0;

	int loanCode;
	int loanYears;
	double loanInterestRate;
	int maximumLoan;
	int minimumLoan;
	int loanAmount;

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


	int line0 = 0;
	string line1 = "";	//to throw in the rest of the first line
	string line2 = "";	//to throw in the headings on second line

	int total = 0;

	if (!inputFile)	//if file doesn't open
	{
		cout << "The input data file failed to open." << endl
			<< "Check to ensure that the file: " << inputFileName << " is a valid file" << endl;


		cin.get();
	}
	else	//file opens
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

			onLine = onLine + 1;

			string errorsOfFailedTests;	//an error test counter
			//error tests to add to the counter
			string originationDateTest = "\n\tInvalid origination date: ";
			string loanAmountTest = "\n\tThe loan amount is outside limits.";
			string numberOfPaymentsMadeTest = "\n\tThe number of payments received is not valid.";
			string loanTypeTest = "\n\tInvalid BRSL Code.";

			//switch to make sure the loan code is valid, the data for now is dummy data
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


			//error testing
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


			//testing if anything is in the string containing the errors
			int stringSize = errorsOfFailedTests.length();	//supplemental text p961

			if (stringSize != 0)
			{
				badLines = badLines + 1;
				cout << endl << employeeID << " " << loanID << " " << loanCode << " "
					<< fixed << setprecision(2) << loanAmount << " " << numberOfPaymentsMade << endl;

				cout << errorsOfFailedTests;

				//adding in the '/' for the date, if the origination date test is in the string of tests
				if (errorsOfFailedTests.find(originationDateTest) != string::npos)	//found in the supplemental text to find strings p965
				{
					cout << originationYear << "/" << originationMonth << "/" << originationDay << endl;
				}
				else
				{
					cout << endl;
				}

			}
			else	//adding the data into parallel arrays
			{
				reg.push_back(region);
				eID.push_back(employeeID);
				lID.push_back(loanID);
				lCode.push_back(loanCode);
				amt.push_back(loanAmount);
				y.push_back(originationYear);
				m.push_back(originationMonth);
				d.push_back(originationDay);
				pmtCount.push_back(numberOfPaymentsMade);

				goodLines = goodLines + 1;
			}
		}	//end of while loop
		cout << endl << badLines << " records with errors, " << goodLines << " records without errors." << endl;
		cout << reg.size() << " records currently stored in parallel vectors." << endl;

		inputFile.close();	//close the file

		//testing if the file loaded into the array
		endSize = reg.size();
		if (endSize > startSize)
		{
			loadSuccess = true;
		}

	}

	cout << "exiting function uploadFile" << endl;

}



void displayRegionDetails(int fileCount, const vector<string> &reg, const vector<string> &lID,
const vector<int> &lCode, const vector<int> &amt,
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


void displayEmployeeDetails(int fileCount, const vector<string> &eID,
	const vector<string> &lID, const vector<int> &lCode,
	const vector<int> &amt, const vector<int> pmtCount)
{
	cout << "Entered function displayEmployeeDetails" << endl;

	string employeeInformation = "";
	long totalEmployeeAmount = 0;

	if (fileCount <= 0)
	{
		//no data files have been loaded
		cout << "No files have been loaded, nothing to display...\n";
	}
	else
	{
		cout << "Enter ID of employee to display: " << endl;
		getline(cin, employeeInformation);

		cout << "Details information of loans processed by employeeID " << employeeInformation << ":" << endl;

		//for loop to find employee information in vectors
		for (int j = 0; j < eID.size(); j++)
		{
			if (eID.at(j) == employeeInformation)
			{
				cout << setw(5) << eID.at(j);
				cout << setw(RDC2) << lID.at(j);
				cout << "  " << setfill('0');
				cout << setfill(' ');
				cout << setw(RDC3) << lCode.at(j);
				cout << setw(RDC4) << amt.at(j);
				cout << setfill(' ');
				cout << setw(4) << pmtCount.at(j);
				cout << endl;
				totalEmployeeAmount += amt.at(j);
			}
		}

		//output a line to separate the data details from the total
		for (int k = 0; k < (RDC1 + RDC2 + RDC3 + RDC4 + 5); k++)
		{
			cout << "-";
		}
		cout << endl;

		//output the total
		cout << setw(RDC1 + 10) << "  Total:" << setw(5 + RDC3 + RDC4) << totalEmployeeAmount << endl;
	}
	
	cout << "Exiting function displayEmployeeDetails" << endl;

}


void displayAllSummary(int fileCount, const vector<int> &lCode,
	const vector<int> &amt, const vector<int> pmtCount)
{
	cout << "Entered function displayAllData" << endl;

	int numberOfLoansOpen = 0;
	int numberOfLoansClosed = 0;

	int loanYears = 0;
	double loanInterestRate = 0.0;
	int maximumLoan = 0;
	int minimumLoan = 0;

	double loanTotalAmtOpen = 0.0;
	double loanTotalAmtClosed = 0.0;

	double totalUnpaidPrincipalOpen = 0.00;
	double totalUnpaidPrincipalClosed = 0.00;

	double cClosedR = 0.00;
	double cOpenR = 0.00;

	double totalPrincipalPaidOpen = 0.00;
	double totalPrincipalPaidClosed = 0.00;

	double cLPrimeOpen = 0.00;
	double cLPrimeClosed = 0.00;
	
	cout << "starting loop to compute totals for " << lCode.size() << " loaded records" << endl;

	for (int f = 0; f < lCode.size(); f++)
	{
		//switch for the loan codes and their corresponding information
		switch (lCode.at(f))
		{
		case 10: loanYears = LOANYEARS10, loanInterestRate = LOANINTERESTRATE10, maximumLoan = MAXIMUMLOAN10, minimumLoan = MINIMUMLOAN10;
			break;
		case 20: loanYears = LOANYEARS20, loanInterestRate = LOANINTERESTRATE20, maximumLoan = MAXIMUMLOAN20, minimumLoan = MINIMUMLOAN20;
			break;
		case 30: loanYears = LOANYEARS30, loanInterestRate = LOANINTERESTRATE30, maximumLoan = MAXIMUMLOAN30, minimumLoan = MINIMUMLOAN30;
			break;
		case 40: loanYears = LOANYEARS40, loanInterestRate = LOANINTERESTRATE40, maximumLoan = MAXIMUMLOAN40, minimumLoan = MINIMUMLOAN40;
			break;
		default:;
		}

		if (pmtCount.at(f) == (loanYears * MONTHS))	//if the loan is CLOSED
		{
			numberOfLoansClosed++;	//counts the number of closed loans

			cClosedR = computeR(loanInterestRate, amt.at(f), MONTHS, loanYears);	//goes to computeR function

			totalPrincipalPaidClosed += cClosedR;	//calculates the total principal paid closed

			cLPrimeClosed = computeLprime(cClosedR, loanInterestRate, MONTHS, loanYears, pmtCount.at(f));	//goes to computeLprime function

			totalUnpaidPrincipalClosed += cLPrimeClosed;	//calculates the total unpaid principal closed

			loanTotalAmtClosed += amt.at(f);	//calculates the loan total amount closed

		}
		else										//if the loan is OPEN
		{
			numberOfLoansOpen++;	//counts the number of open loans
			
			cOpenR = computeR(loanInterestRate, amt.at(f), MONTHS, loanYears);	//goes to computeR function

			totalPrincipalPaidOpen += cOpenR;	//calculates the total principal paid closed

			cLPrimeOpen = computeLprime(cOpenR, loanInterestRate, MONTHS, loanYears, pmtCount.at(f));	//goes to computeLprime function

			totalUnpaidPrincipalOpen += cLPrimeOpen;	//calculates the total unpaid principal open

			loanTotalAmtOpen += amt.at(f);	//calculates the loan total amount closed

		}

	}


	if (fileCount == 1)
	{
		cout << "\n\t\tSummary report for the " << fileCount << " file that has been loaded" << endl;
	}
	else if (fileCount > 1)
	{
		cout << "\n\t\tSummary report for the " << fileCount << " files that have been loaded" << endl;
	}
	
	cout << endl << "\tNumber" << "\t        Total Amt." << "\tPrincipal" << "\tPrincipal" << endl;
	cout << "Status " << "\tof Loans " << "\tLoaned " << "\t        Paid " << "\t        Unpaid " << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "  Open: " << setw(8) << numberOfLoansOpen << " " << setw(16) << fixed << setprecision(2) << loanTotalAmtOpen << " "
		<< setw(16) << fixed << setprecision(2) << loanTotalAmtOpen - totalUnpaidPrincipalOpen << " "
		<< setw(16) << fixed << setprecision(2) << totalUnpaidPrincipalOpen << endl;
	cout << "Closed: " << setw(8) << numberOfLoansClosed << " " << setw(16) << fixed << setprecision(2) << loanTotalAmtClosed << " "
		<< setw(16) << fixed << setprecision(2) << loanTotalAmtClosed - totalUnpaidPrincipalClosed << " "
		<< setw(16) << fixed << setprecision(2) << totalUnpaidPrincipalClosed << endl;


}

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

	//cout << "Entered function computeR" << endl;

	//implementation code goes here

	double one = 1.000000;

	double interestOverMonths = 0.00;
	interestOverMonths = (interestRate / MONTHS);
	//cout << "interest over months " << interestOverMonths << endl;

	R = ((loanAmount * interestOverMonths) / (one - (pow(one + interestOverMonths, (-one * (MONTHS*lengthOfLoanInYears))))));


	//cout << "Exiting function computeR" << endl;

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

	//cout << "Entered function computeLprime" << endl; //output for testing and development

	double interestRateI = interestRate / paymentsPerYear;

	//calculate L'
	double LprimeExp = (-1 * ((paymentsPerYear * lengthOfLoanInYears) - paymentsReceived));
	double LprimeNumerator = (1 - (pow((1 + interestRateI), LprimeExp)));
	double Lprime = R * (LprimeNumerator / interestRateI);

	//cout << "Exiting function computeLprime" << endl; //output for testing and development

	return Lprime;

} //END function computeLprime



void clearAllVectors(int &fileCount, vector<string> &reg, vector<string> &eID,
	vector<string> &lID, vector<int> &lCode, vector<int> &amt,
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

