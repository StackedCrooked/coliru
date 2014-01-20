#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  int n = COUNT ;
  pid_t childpid;
  int i, j;

  for ( i = 0; i < n; i++ ) {
    for ( j = 0; j < n; j++ ) {
      if ( ( childpid = fork()) > 0 )
        break;
    }
    wait (NULL);        // wait for child
  }
  wait (NULL);  // wait for child
  
  FILE* file = fopen( "pids", "a+" ) ;
  fprintf( file, "pid: %u childpid: %u\n", getpid(), childpid ) ;
  fclose(file) ;
}
