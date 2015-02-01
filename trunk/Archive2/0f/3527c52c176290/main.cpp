#include<unistd.h>
#include<sys/wait.h>
#include<chrono>
#include<vector>
#include<iostream>
#include<sstream>
#include<cerrno>
#include<cstring>
#include<cstdlib>

std::string format_time(std::chrono::high_resolution_clock::duration duration)
{
    std::vector<uint64_t> counts(5);
    counts[0] = std::chrono::duration_cast<std::chrono::hours>(duration).count();
    counts[1] = std::chrono::duration_cast<std::chrono::minutes>(duration).count()%60;
    counts[2] = std::chrono::duration_cast<std::chrono::seconds>(duration).count()%60;
    counts[3] = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()%1000;
    counts[4] = std::chrono::duration_cast<std::chrono::microseconds>(duration).count()%1000;

    std::stringstream ss;
    auto first_used = -1;
    for(auto i = 0; i < 5; i++)
    {
        if(counts[i] != 0)
        {
            first_used = i;
            break;
        }
    }
    switch(first_used)
    {
        case 0 : ss << counts[0] << " hours, ";
        case 1 : ss << counts[1] << " minutes, ";
        case 2 : ss << counts[2] << " seconds, ";
        case 3 : ss << counts[3] << " milliseconds, ";
        case 4 : ss << counts[4] << " microseconds."; break;
        default: ss << "No time used";
    }
    return ss.str();
}

std::vector<std::string> parse_string(std::string command)
{
    std::vector<std::string> args;
   
    bool cont = true;
    auto pos = static_cast<std::string::size_type>(0);
    while(cont)
    {
        //Parse the remaining substring
        command = command.substr(pos);

        //Trim whitespace from new substring
        auto firstChar = command.find_first_not_of(" \t");
        if(firstChar == std::string::npos) command = ""; 
        auto lastChar = command.find_last_not_of(" \t"); 
        command = command.substr(firstChar, lastChar-firstChar+1);

        //Find a space and parse the argument up to that space
        pos = command.find(' ');
        if(pos == std::string::npos) cont = false; //this is the last argument, tack it on and break out of the loop
        args.push_back(command.substr(0,pos));
    }
    return args;
}

int main(void)
{
    using clock = std::chrono::high_resolution_clock;

    bool cont = true;
    std::vector<std::string> history;
    clock::duration ptime_recent{0};
    clock::duration ptime_total{0};

    while(cont)
    {
        //get a command from the user and parse it
        std::cout << "[0;31;40m[cmd]:    [0;37;40m";
        std::string command;
        std::getline(std::cin,command);
       
        if(command.size() == 0) continue;
        history.push_back(command);

        auto args = parse_string(command);
        if(args.size() == 0)
        {
            std::cerr << "Parsing Error - No args returned" << std::endl;
            continue;
        }
    
        if(args[0] == "help")
        {
            std::cout <<
                "Basic Shell Program" << std::endl <<
                "help       --Opens this help prompt" << std::endl <<
                "cd         --Changes current working directory" << std::endl <<
                "history    --Displays full command history" << std::endl <<
                "^ (number) --Displays command (number) in the command history" << std::endl <<
                "ptime      --Displays processing time of most recent process" << std::endl <<
                "ptime total --Displays total processing time of all processes" << std::endl <<
                "exit       --Exits shell" << std::endl;
        }
        else if(args[0] == "cd")
        {
            if(args.size() < 2)
            {
                std::cerr << "Not enough arguments provided" << std::endl;
                continue;
            }
            auto dir_code = chdir(("./" + args[1]).data());
            if(dir_code != 0) std::cerr << "CWD Change Failed: " << std::strerror(errno) << std::endl;
        }
        else if(args[0] == "history")
        {
            for(auto && com : history)
                std::cout << com << std::endl;
        }
        else if(args[0] == "^")
        {
            if(args.size() < 2)
            {
                std::cerr << "Not enough arguments provided" << std::endl;
                continue;
            }
            auto comNum = std::atoi(args[1].data());
            if(comNum > history.size() || comNum < 1)
            {
                std::cerr << "Invalid argument" << std::endl;
                std::cerr << "Valid arguments are integers between 1 and " << history.size() << "(history size)" << std::endl;
                continue;
            }
            std::cout << history[comNum - 1] << std::endl;
        }
        else if(args[0] == "ptime")         
        {
            if(ptime_recent.count() == static_cast<clock::duration::rep>(0))
            {
                std::cout << "No processes have run" << std::endl;
                continue;
            }
            if(args.size() < 2)
                std::cout << "Time spent executing most recent child process: " << format_time(ptime_recent) << std::endl;
            else
                if(args[1] == "total")
                    std::cout << "Total time spent exeuting child processes: " << format_time(ptime_total) << std::endl;
                else
                    std::cerr << "Invalid argument" << std::endl;
        }
        else if(args[0] == "exit")
        {
            cont = false;
            return 0;
        }
        else{
            auto start = clock::now();
            auto pid = fork();
            if(pid < 0)
            {
                std::cerr << "Fork error: " << std::strerror(errno) << std::endl;
                return 2;
            }
            if(pid == 0)
            {
                //Build and execute child process
                std::vector<char*> charStarArgs;
                charStarArgs.reserve(args.size());
                for(auto&& str : args)
                    charStarArgs.push_back(const_cast<char*>(str.data()));
                charStarArgs.push_back(nullptr);
                execvp(charStarArgs[0],const_cast<char*const*>(charStarArgs.data()));
                std::cerr << "Process could not execute: " << std::strerror(errno) << std::endl;
            }
            else
            {
                //Shell waits for child process
                waitpid(pid,nullptr,0);
                auto end = clock::now();
                ptime_recent = end - start;
                ptime_total += ptime_recent;
            }
        }
    }
    return 0;
}
