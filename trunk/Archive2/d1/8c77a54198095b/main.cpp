#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>

//using namespace std;

//char letters[] = { 'a', 'b', 'c' };
static const char letters[] =
"0123456789"
"!@#$%^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

template <typename T, std::size_t N>/*Why can't this line just be "template <typename T>"? 
    								Because then you cannot tell that you want an array here.*/
std::size_t array_size(T(&)[N])
{
	return N;/*It is called safe array size: if you call it on naything not an array, it will 
			 give you an error (unlike sizeof which often returns size of pointer instead of array)*/
}
bool next(std::string& in)//Mutates string, setting it to the next in set of all possible combinations. 
						  //If you run provided code you will see how is it done. It returns true if there 
						  //was no "rollover" (like preventing a car milage meter from displaying "0000"
						  //after exceeding "9999"), false otherwise. This is intended to prevent the
						  //generation of a possible combination more than once. "next" is a reference
						  //variable to the current combination being generated.
{
	for (std::size_t i = 0; i < in.size(); ++i)
		if (in[i] == letters[array_size(letters) - 1]){ //if current letter is last in set ...

		in[i] = letters[0]; //Then we assign first letter and let loop continue

		}//end of "if (in[i] == letters[array_size(letters) - 1])"
		else {
			std::size_t pos = std::distance(std::begin(letters),
				//Computes the distance between two iterators. It's used to find
				//the distance between the beginning of letters array and the pointer 
				//to the currently found element (to get the index of that element) in
				//the array

				std::find(std::begin(letters), std::end(letters), in[i]));//"in[i]" is the second iterator that
			                                                              //looks for the current letter being
			                                                              //pointed to in letters array
			
			in[i] = letters[++pos]; //Else we increment the index and use it to assign 
			                        //the next letter in the set and return true.
			
			return true; //As indication that it is not the last possible string  
												
		}//end of else statement
		return false; //If loop finished, we exhausted all strings
		
}//closing brace of bool next

void print_all()
{
	std::string password = "sam40";//password to be guessed
	const std:: size_t max = 5;//maximum password string length to guess for 
	for (std::size_t size = 1; size <= max; ++size) {//Generate sequences of all possible length
		//Create string of correspomding length. Note that we CANNOT use space as initializer
		//Or nothing would work at all.
		std::string guess(size, letters[0]);
		bool again = false;
		do { //Inner loop, generates all possible variation of given length
			again = next(guess); //Generate next string 			
			/*see reference to class template instantiation 'std::iterator_traits<std::string>' being compiled*/
			//std::cout << guess << '\n';
                	if (guess == password){
			std::cout << "The password is: " << guess << std::endl;
            return;
		}
		} while (again);/*Is the loop logic still broken?*/

		//std::cout << '\n';

	}//end of for loop
}

int main()
{
	print_all();
}