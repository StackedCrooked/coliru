#include <csignal>
#include <iostream>
 
void signal_handler(int signal)
{
    std::cout << "Received signal " << signal << '\n';
}
 
int main()
{
    // Install a signal handler
    std::signal(SIGINT, signal_handler);
 
    std::cout << "Sending signal " << SIGINT << '\n';
    std::raise(SIGINT);
}