#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <regex>
#include <algorithm>
#include <filesystem>
#include <sstream>

#include "user_typedefs.hpp"

using namespace std;
using namespace utd; //user_typedefs.hpp namespace
using namespace std::tr2::sys;

/*********************   Function Prototypes   ***************************/
//main search lookup prototype
void main_look_up(const path &, utd::mapFileData &, regex &);

//making switch prototype
void toggle_Switches(string);

//help prototype
void displayHelp();

//Converting type to string prototype
template<typename T>
string convert_type_to_string(T myType);

//Printing the table prototype
void print_as_string(vectorMapData &);

/***************************   Switch struct   ***************************/
//The [h] switch is not needed since it can be called directly if/when found.
struct SwitchTypes{
bool cpp_switch,    	//[c]
	 java_switch,		//[j]
	 multimedia_switch, //[m]
	 regex_switch,		//[x] [expression]
	 reverse_sort,		//[R]
	 size_sort,			//[s]
	 recursive_search,  //[r]
	 no_search;			//doesn't search for specific files.
} switchOption = {false, false, false, 
				  false, false, false, 
				  false, false};

/*************************************************************************/

int main(int argc, char* argv[]){
	locale here("");
	cout.imbue(here);
	regex *userRegex = nullptr;
	string parameters = "";
	path myPath = "";
	//Check parameters for 1 parameters.
	if(argc == 1){
		myPath = ".";
	}
	//Check parameters for 2 parameters.
	if(argc == 2){
		if(argv[1][0] == '-'){
			for(unsigned j=0; j<strlen(argv[1]); j++){
				parameters += argv[1][j];
			}
			myPath = "."; //set current dir as search path
		} else {
			myPath = argv[1];
		}
	}
	//Check parameters for 3 parameters.
	if(argc == 3){
		if(argv[1][0] == '-'){
			for(unsigned j=0; j<strlen(argv[1]); j++){
				parameters += argv[1][j];
			}
			if(parameters.find('x') != string::npos){
				myPath = ".";
				try{
					userRegex = new regex(argv[2]);
				} catch (regex_error e){
					cout << "An error occurred: " << e.what()
						 << "\nUSAGE: fileusage [-rRscjmx [regular expression]] [folder]\n";
					return EXIT_FAILURE;
				}
			} else {
				myPath = argv[2];
			}
		} else {
			cerr << "An error has occurred, invalid parameters entered\n"
				 << "USAGE: fileusage [-rRscjmx [regular expression]] [folder]\n";
			return EXIT_FAILURE;
		}
	}
	//Check input for 4 parameters.
	if(argc == 4){
		if(argv[1][0] == '-'){
			for(unsigned j=0; j<strlen(argv[1]); j++){
				parameters += argv[1][j];
			}
			if(parameters.find('x') != string::npos){
				try{
					userRegex = new regex(argv[2]);
				} catch (regex_error e){
					cout << "an error occurred: " << e.what() << endl;
					return EXIT_FAILURE;
				}
				myPath = argv[3];
			} else {
				cerr << "An error Occurred: Invalid Parameter\n"
				     << "USAGE: fileusage [-rRscjmx [regular expression]] [folder]\n";
				return EXIT_FAILURE;
			}
		} else {
			cerr << "An error has occurred, invalid parameters entered\n"
				 << "USAGE: fileusage [-rRscjmx [regular expression]] [folder]\n";
			return EXIT_FAILURE;
		}
	}
	//Check if parameters are greater than 4, then they're wrong.
	if(argc > 4){
		cerr << "An error has occured: To many parameters entered.\n"
			 << "USAGE: fileusage [-rRscjmx [regular expression]] [folder]\n";
		return EXIT_FAILURE;
	}

	//Check if the path exists.
	if(!exists(myPath)){
		cerr << "\"" << myPath.string() << "\" Does not exist, check spelling of your path.\n"
			 << "USAGE: fileusage [-rRscjmx [regular expression]] [folder]\n";
		return EXIT_FAILURE;
	}
	cout << "Scanning: \"" << myPath << "\"\n";

	//Turn on appropriate switches.
	toggle_Switches(parameters);
	
	//Create a map to hold the extension and a pair of occur and file size.
	utd::mapFileData searchResults;

	LARGE_INTEGER start, end, freq;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	main_look_up(myPath, searchResults, *userRegex);
	QueryPerformanceCounter(&end);
	double timeElapsed = double(end.QuadPart - start.QuadPart) / freq.QuadPart;
	
	utd::vectorMapData searchResultsv(searchResults.begin(), searchResults.end());
	
	if(switchOption.size_sort){
		//using a Lambda function to sort the list in Min to Max order.
		sort(searchResultsv.begin(), searchResultsv.end(), 
			[](pair<string, utd::numericFileDetail> &f1, pair<string, utd::numericFileDetail> &f2){
				return f1.second.second < f2.second.second; 
			}
		);
	}

	//Reverse the vector of map contents
	if(switchOption.reverse_sort){
		reverse(searchResultsv.begin(), searchResultsv.end());
	}

	//output the table to the user.
	print_as_string(searchResultsv);

	cout << "It took: " << timeElapsed << " seconds"<<endl;

	//delete the userRegex pointer if it's not null or if it was enabled and somehow not used.
	if(switchOption.regex_switch || userRegex != nullptr){
		delete userRegex;
	}
}

//This is the function to search for the switches as numbers.
void main_look_up(const path &searchPath, utd::mapFileData &searchContent, regex &userRegex){
	directory_iterator dirItr(searchPath), eod;
	path totalFilePath;
	for(; dirItr != eod; dirItr++){
		totalFilePath = searchPath / dirItr->path();
		if(!is_directory(dirItr->status())){
			//Search for all the files.
			if(switchOption.no_search){
				++searchContent[dirItr->path().extension()].first;
				searchContent[dirItr->path().extension()].second += file_size(totalFilePath);
			}
			//Search for C based files.
			if(switchOption.cpp_switch && regex_match(dirItr->path().extension(), regex("\\.(c|cpp|h|hxx|hpp)$"))){
				++searchContent[dirItr->path().extension()].first;
				searchContent[dirItr->path().extension()].second += file_size(totalFilePath);
			}
			//Search for Java files.
			if(switchOption.java_switch && regex_match(dirItr->path().extension(), regex("\\.(class|java)$"))){
				++searchContent[dirItr->path().extension()].first;
				searchContent[dirItr->path().extension()].second += file_size(totalFilePath);
			}
			//Search for multimedia files.
			if(switchOption.multimedia_switch && regex_match(dirItr->path().extension(), regex("\\.(avi|mkv|mpeg|mp4|mp3)$"))){
				++searchContent[dirItr->path().extension()].first;
				searchContent[dirItr->path().extension()].second += file_size(totalFilePath);
			}
			//Search for the users regular expression.
			try{
				if(switchOption.regex_switch && regex_match(dirItr->path().extension(), userRegex)){
					++searchContent[dirItr->path().extension()].first;
					searchContent[dirItr->path().extension()].second += file_size(totalFilePath);
				}
			} catch (regex_error e){
				cerr << "Error occurred: " << e.what() << endl;
				exit(EXIT_FAILURE);
			}
		} else {
			if(switchOption.recursive_search){
				//Recurse though the directory if the user entered [r].
				main_look_up(totalFilePath, searchContent, userRegex);
			}
		}
	}
}

//This function triggers which switches should be enabled.
void toggle_Switches(string mySwitches){
	//remove the '-' from the switches
	if(mySwitches.find('-') != string::npos){
		mySwitches.erase(remove(mySwitches.begin(), mySwitches.end(), '-'), mySwitches.end());
	}

	string switchChars = "";
	/*
	  go though each element in the string and add to switchChars in order to find
	  duplicates
	*/
	for(auto mySwitch : mySwitches){
		if(switchChars.find(mySwitch) != string::npos){
			continue;
		}
		switchChars += mySwitch;
		//Choose which switch should be used.
		switch(mySwitch){
			case 'j' : switchOption.java_switch = true;
					   break;
			case 'c' : switchOption.cpp_switch = true;		 
					   break;
			case 'm' : switchOption.multimedia_switch = true; 
					   break;
			case 'x' : switchOption.regex_switch = true; 
					   break;
			case 's' : switchOption.size_sort = true; 
					   break;
			case 'R' : switchOption.reverse_sort = true; 
					   break;
			case 'r' : switchOption.recursive_search = true; 
					   break;
			case 'h' : displayHelp();
					   exit(EXIT_SUCCESS);
			default  : cout << mySwitch << " is an un-handled switch\n"
						    << "Please try entering a handled switch\n"
							<< "enter -h for more information on handled switches\n"
							<< "USAGE: Usage: fileusage [-rRscjmx [regular expression]] [folder]\n";
					   exit(EXIT_FAILURE);
		}
	}
	//default to search for everything if no switches are entered related to searching.
	if(!switchOption.java_switch && !switchOption.cpp_switch && !switchOption.multimedia_switch && !switchOption.regex_switch){
		switchOption.no_search = true;
	} else {
		switchOption.no_search = false;
	}
}

/*
  This function take in a generic type and converts it into a string
  It also take in consideration of ',' from locale.
*/
template<typename T>
string convert_type_to_string(const T myType){
	locale here("");
	stringstream ss;
	ss.imbue(here);
	ss << myType;
	return ss.str();
}

/*
  This function allows the vector to be printed out as a string
  it does not return anything and only outputs the table.
*/
void print_as_string(utd::vectorMapData &vect){
	utd::vectorMapData::iterator itr = vect.begin();

	utd::ull extensionSizeMax = 0;
	utd::ull occuranceSizeMax = 0;
	utd::ull fileSizeMax	  = 0;

	int fileExtensionCount		 = 0;
	utd::ull totalOccuranceCount = 0;
	utd::ull totalFileSizeCount  = 0;

	vector<unsigned> extensionStringSizes;
	vector<unsigned> occuranceStringSizes;
	vector<unsigned> fileStringSizes;

	//find each size of the map so it can format the columns correctly.
	for(; itr != vect.end(); itr++){
		++fileExtensionCount;
		totalOccuranceCount += itr->second.first;
		totalFileSizeCount  += itr->second.second;

		string occurance = convert_type_to_string(itr->second.first);
		string fileSize = convert_type_to_string(itr->second.second);

		extensionStringSizes.push_back(itr->first.size());
		occuranceStringSizes.push_back(occurance.size());
		fileStringSizes.push_back(fileSize.size());

		if(extensionSizeMax < itr->first.size()){
			extensionSizeMax = itr->first.size();
		}
	}

	//creat the total file size title and make the total count a string
	string totfileSize = convert_type_to_string(totalFileSizeCount);
	const string FIL_SIZE = "File Size";

	//find the max sting for default column size
	fileSizeMax = totfileSize.size();
	if(fileSizeMax < FIL_SIZE.size()){
		fileSizeMax = FIL_SIZE.size();
	}

	//creat the title for occurances and convert the total count to a string
	string totOccuranceSize = convert_type_to_string(totalOccuranceCount);
	const string OCC_TITLE = "Occur";

	//find the max field for occurances and set it to the column width
	if(OCC_TITLE.size() < totOccuranceSize.size()){
		occuranceSizeMax = totOccuranceSize.size();
	} else {
		occuranceSizeMax = OCC_TITLE.size();
	}

	//create the title for extension size and convert the extension count to a string to format for the table
	string totExtensionSize = convert_type_to_string(fileExtensionCount);
	const string EXT_TITLE = "Extension";

	//find the max extension size.
	if(extensionSizeMax < totExtensionSize.size()){
		extensionSizeMax = totExtensionSize.size();
	}
	if(extensionSizeMax < EXT_TITLE.size()){
		extensionSizeMax = EXT_TITLE.size();
	}
	//output a separator line.
	cout << " \332\304" << string(static_cast<int>(extensionSizeMax), '\304') <<"\304\302\304" 
		 << string(static_cast<int>(occuranceSizeMax), '\304') << "\304\302\304"
		 << string(static_cast<int>(fileSizeMax), '\304') << "\304\277\n";
	//output the titles of each column
	cout << " \263 " << string(static_cast<int>(extensionSizeMax - EXT_TITLE.size()), ' ') << EXT_TITLE << " \263 "
		 << string(static_cast<int>(occuranceSizeMax - OCC_TITLE.size()), ' ') << OCC_TITLE << " \263 "
		 << string(static_cast<int>(fileSizeMax - FIL_SIZE.size()), ' ') << FIL_SIZE << " \263\n";
	//output a separator line
	cout << " \303\304" <<string(static_cast<int>(extensionSizeMax), '\304') << "\304\305\304" 
		 << string(static_cast<int>(occuranceSizeMax), '\304') << "\304\305\304" 
		 << string(static_cast<int>(fileSizeMax), '\304') << "\304\264\n";

	int i=0;
	itr = vect.begin();
	//output the data from the map as a string.
	for(;itr != vect.end(); itr++, i++){
		cout << " \263 " << string(static_cast<int>(extensionSizeMax - extensionStringSizes.at(i)), ' ') << itr->first << " \263 "
			 << string(static_cast<int>(occuranceSizeMax - occuranceStringSizes.at(i)), ' ') << itr->second.first << " \263 "
			 << string(static_cast<int>(fileSizeMax - fileStringSizes.at(i)), ' ') << itr->second.second << " \263\n";
	}
	//outputs the line between the occurance and total size data
	cout << " \303\304" <<string(static_cast<int>(extensionSizeMax), '\304') << "\304\305\304" 
		 << string(static_cast<int>(occuranceSizeMax), '\304') << "\304\305\304" 
		 << string(static_cast<int>(fileSizeMax), '\304') << "\304\264\n";
	
	//outputs to total sizes of the 3 columns
	cout << " \263 " << string(static_cast<int>(extensionSizeMax - totExtensionSize.size()), ' ') << totExtensionSize << " \263 "
		 << string(static_cast<int>(occuranceSizeMax - totOccuranceSize.size()), ' ') << totOccuranceSize << " \263 "
		 << string(static_cast<int>(fileSizeMax - totfileSize.size()), ' ') <<  totfileSize << " \263\n";

	//outputs the bottom line of the Table
	cout << " \300\304" <<string(static_cast<int>(extensionSizeMax), '\304') <<"\304\301\304" 
		 << string(static_cast<int>(occuranceSizeMax), '\304') << "\304\301\304"
		 << string(static_cast<int>(fileSizeMax), '\304') << "\304\331\n";
}

//Display the help to the user
void displayHelp(){
	cout << "-c: search for c++ files (c++ files extension: .c,.cpp,.h,.hpp,.hxx)\n"
		 << "-j: search for java files (java files extension: .java,.class)\n"
		 << "-m: search for multimedia files (multimedia files extension: .avi,.mkv,.mpeg,.mp4,.mp3)\n"
		 << "-x: search extensions using a regex expression (ie:  -x \"\\.(docx|xlsx)\")\n"
		 << "-r: process all folders recursively.\n"
		 << "-R: list the files in reverse order.\n"
		 << "-s: sort the files by ascending file size – or descending if the R switch is provided.\n";

	cout << "\nSwitches can be entered with more than one at a time as so:\n"
		 << "USAGE: Usage: fileusage [-rRscjmx [regular expression]] [folder]\n";
}