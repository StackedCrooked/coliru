/*
    strok multithread problem  demo

    
DISCLAIMER:

I'm not neither a thread nor C++ Ninja

This is just a simple test, which *might* be wrongly presented.
AFAIK, there doesn't appear any kind of Undefined/Unspecified behavior

    Prashant Srivastava (_P0W!)
*/

#include <boost/thread.hpp>
#include <iostream>
#include <cstring>

using namespace std;

std::vector<std::string> v1,v2,v3,v4;

/* 
Following version of strotok is taken from 
    http://www.opensource.apple.com/source/Libc/Libc-167/string.subproj/strtok.c
*/

char *mystrtok(char *s , const char *delim )

{
    char *spanp;
	int c, sc;
	char *tok;
	static char *last;

	if (s == NULL && (s = last) == NULL)
		return (NULL);

cont:
	c = *s++;
	for (spanp = (char *)delim; (sc = *spanp++) != 0;) {
		if (c == sc)
			goto cont;
	}

	if (c == 0) {		
		last = NULL;
		return (NULL);
	}
	tok = s - 1;
	for (;;) {
		c = *s++;
		spanp = (char *)delim;
		do {
			if ((sc = *spanp++) == c) {
				if (c == 0)
					s = NULL;
				else
					s[-1] = 0;
				last = s;
				return (tok);
			}
		} while (sc != 0);
	}

}


char* mystrtok_r  ( char *str, const char *delim, char **nextp)
{
    char *ret;

    if (str == nullptr)
    {
        str = *nextp;
    }

    str += std::strspn(str, delim);

    if (*str == '\0')
    {
        return nullptr;
    }

    ret = str;

    str += std::strcspn(str, delim);

    if (*str)
    {
        *str++ = '\0';
    }

    *nextp = str;

    return ret;
}

void ThreadFunction1()
{

    char input[] = "P0W PRASHANT JACK KING QUEEN RAJ CHAUDHARY";
   
    char *token = mystrtok(input, " ");
    while (token != NULL) {
  
        v1.push_back( token );

        token = mystrtok(NULL, " ");
        boost::this_thread::sleep(boost::posix_time::milliseconds(50));
    }

}

void ThreadFunction2()
{

    char input[] = "A quick brown fox jumps over lazy dog";
    char *token = mystrtok(input, " ");
    while (token != NULL) {
        v2.push_back( token );
        token = mystrtok(NULL, " ");
        boost::this_thread::sleep(boost::posix_time::milliseconds(50));
    }
    
}


void ThreadFunction3()
{
    char input[] = "P0W PRASHANT JACK KING QUEEN RAJ CHAUDHARY"; 
    char *rest; 
    char *token; 
    char *ptr = input; 

    while( (token = mystrtok_r(ptr, " ", &rest)) ) 
    {
        v3.push_back( token );
        ptr = rest;   
        boost::this_thread::sleep(boost::posix_time::milliseconds(50));
    }

}

void ThreadFunction4()
{
    char input[] = "A quick brown fox jumps over lazy dog"; 
    char *rest;               
    char *token; 
    char *ptr = input; 

    while( (token = mystrtok_r(ptr, " ", &rest)) ) 
    {
        v4.push_back( token );
        ptr = rest;   
        boost::this_thread::sleep(boost::posix_time::milliseconds(50));
    }
}

void dipplayVectors( const std::vector<std::string>& v, const std::string& msg )
{
    std::cout << msg << ": " ;
    for(const auto &x: v)
        std::cout << x <<" - ";
    std::cout << std::endl ;
}

int main()
{


    // Start thread
    boost::thread t1(&ThreadFunction1);    
    boost::thread t2(&ThreadFunction2);
    boost::thread t3(&ThreadFunction3);
    boost::thread t4(&ThreadFunction4);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    
    
    dipplayVectors( v1, "Vector v1" );
    dipplayVectors( v2, "Vector v2" );

    dipplayVectors( v3, "Vector v3" );
    dipplayVectors( v4, "Vector v4" );  
        
    return 0;
}


