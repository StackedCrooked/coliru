#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

int main()
{
    // create a test file
    const char* const file_name =  "test_file.txt" ;
    {
        const std::string text =
            "Shall I compare thee to a summer's day? Thou art\n"
            "more lovely and more temperate. Rough winds do\n"
            "shake the darling buds of May! And summer's lease\n"
            "hath all too short a date. Sometime too hot the eye\n"
            "of heaven shines. And often is his gold complexion dimm'd!\n"
            "And every fair from fair sometime declines. By chance,\n"
            "or nature's changing course untrimm'd.\n" ;
        std::ofstream(file_name) << text ;
    }
    
    // verify that the test file has been created correctly
    { 
        std::cout << "\n-------- the file contains ------------------\n"
                  << std::ifstream(file_name).rdbuf() 
                  << "------------------------------------------------\n" ;
    }
    
    std::ifstream inFile(file_name) ; // open the file for input
    
    vector<string> sentence ;
    string curr_sentence ; // current sentence being built
    string curr_word ; // the word just read
    const string sentence_enders = "?!." ;

    // read word by word from the file until input fails
    while( inFile >> curr_word ) // for each word read
    {
        curr_sentence += curr_word ; // add word to current sentence

        // if the current word ends with a sentence ender
        if( sentence_enders.find( curr_word.back() ) != string::npos )
        // or: if( sentence_enders.find( curr_word[ curr_word.size() - 1 ] ) != string::npos )
        {
            // this is the end of the sentence.
            sentence.push_back( curr_sentence ) ; // add current sentence to sentence vector
            curr_sentence= "" ; // and begin a new empty sentence
        }

        else curr_sentence += ' ' ; // put a space between this and the next word
    }

    // add the last sentence even if no sentence ender was found
    if( !curr_sentence.empty() ) sentence.push_back( curr_sentence ) ;


    std::cout << "sentences extracted:\n--------------------\n" ;
    for ( std::size_t i = 0; i < sentence.size(); i++)
    {
        cout << '\t' << i << ". " << sentence[i]  << /*endl*/ '\n';
    }
}