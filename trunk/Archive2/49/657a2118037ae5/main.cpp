#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;

int main() {
        char line[200];
#define CPP11
#ifdef CPP11
        // using C++11 raw string literals
        char command[] = R"(
                            ls /
                            exit 33
                         )";
#else
        // using classical string literals 
        char command[] = "ls /"         "\n"
                         "exit 33"      "\n";
#endif
    //  system(command);
        FILE *fp = popen(command, "r");
        while (fgets(line, (sizeof line) - 1, fp)) {
            printf("-> %s", line);
        }
        auto rc = pclose(fp);
        printf("rc = %d\n", (rc>>8));
}