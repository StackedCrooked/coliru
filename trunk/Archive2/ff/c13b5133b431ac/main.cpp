#include <pthread.h>
#include <unistd.h>
#include <sched.h>
#include <string.h>

#include <chrono>
#include <iostream>
#include <memory>
#include <regex>

int main(int argc,char* argv[],char* env[])
{
    const char* regexstr = "(.*\\.)?mos.ru";
    
    std::cerr << std::regex_match(std::string("abc.mos.ru"),std::regex(regexstr))   << std::endl;; 
    std::cerr << std::regex_match(std::string("mos.ru"),std::regex(regexstr))       << std::endl;
    std::cerr << std::regex_match(std::string("pornomos.ru"),std::regex(regexstr))  << std::endl;


}
