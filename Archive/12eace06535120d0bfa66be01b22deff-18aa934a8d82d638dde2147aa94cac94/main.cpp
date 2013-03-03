/*
 * Program : Basic Algebra Parser
 * Creator : Quazi Nafiul Islam
 * Date    : 03 - Mar - 2013
 * 
 * University Credentials:
 * ID     : 1210139042
 * Course : CSE 225
 * 
 * Instructions :
 */

// For basic input/output
#include <iostream>
// For taking string input
#include <string>
// For making a string stream
#include <sstream>
// For the use of the vector class
#include <vector>
// For simplifying certain processes
#include <algorithm>

// Function to tokenize strings
std::vector<std::string> tokenize(const std::string & str, std::vector<char> & operators) {
    // Vector to keep all tokens in
	std::vector<std::string> allTokens;
	// stringstream for splitting
	std::stringstream ss(str);
	// Variable to store tokens in
	std::string token;

	// Main loop to put tokens in allTokens
	for ( unsigned int i = 0; std::getline(ss, token, i >= operators.size() ? ' ' : operators.at(i)); i++ ) {
		allTokens.push_back(token);
	}
	return allTokens;
}

std::vector<char> getOperators( const std::string & str ) {
	std::vector<char> operators;
	for ( char c : str ) {
		if ( c == '+' || c == '=' || c == '-' || c == '*' || c == '/' || c == '^') {
			operators.push_back(c);
		}
	}	
	return operators;
}

// template <class returnType>
// returnType evaluateTokens(std::vector<string> & allTokens) {
// 
// }

int main ( void ) {

	// Version Output
	std::cout << "Basic Algebra RDP Version 0.1 Alpha" << std::endl;
	std::cout << "\n";

	// Instructions for input
	std::cout << "If you wish to close console, please type \"close\" without the quote-marks" << std::endl;

	// Variable for input
	std::string userInput;
	std::vector<std::string> tokens;
	std::vector<char> operators;

	// Main loop for console functionality
	while (userInput != "close") {
		std::cout << ">>> ";
		std::getline(std::cin, userInput);
		std::cout << std::endl;
		std::remove_if(userInput.begin(),userInput.end(),isspace);
		operators = getOperators(userInput);
		tokens  = tokenize(userInput,operators);
		for (std::string token : tokens) {
			std::cout << token << std::endl;
		}	
		for ( char c : operators) {
			std::cout << c << std::endl;
		}
		std::cout << std::endl;
	}
	return 0;
}