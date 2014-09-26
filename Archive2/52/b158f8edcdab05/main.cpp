#include <iostream>
#include <getopt.h>
#include <vector>

int main(int argc, char* argv[])
{
    std::vector<char*> args(argv, argv + argc);
    int opt_index = 0;
    option long_options[] = { 
        { "help",    no_argument, nullptr, 'h' },
        { "version", no_argument, nullptr,  0  },
        { 0, 0, 0, 0 } 
    };
    int c;
    while ((c = getopt_long(argc, args.data(), "hv", long_options, &opt_index)) != -1)
    {
        switch (c)
        {
            case 0:
                if (long_options[opt_index].flag != 0)
                    break;
                break;
                
            case 'h':
                std::cerr << "help\n";
                return 1;
            case 'v':
                std::cerr << "version 0.0.1\n";
                return 1;
                
            case '?':
                return -1;
            default:
                return -1;
        }
    }
    
    return 0;
}
