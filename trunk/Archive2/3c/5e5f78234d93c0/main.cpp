#include <array>
#include <iostream>

#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int subProc(void *data) {
    sleep(1);
    return 123;
}

int main(int argc, char *argv[]) {
	auto stack = new std::array<char, 1024>;

	int tid = clone(&subProc, stack->end(), SIGCHLD, NULL);
    
	int status;
	waitpid(tid, &status, 0);
	if(WIFEXITED(status)) {
		std::cout << "Returned " << WEXITSTATUS(status) << ".\n";
	} else if(WIFSIGNALED(status)) {
    	std::cout << "Killed by signal " << WTERMSIG(status) << ".\n";
	}
	return 0;
}