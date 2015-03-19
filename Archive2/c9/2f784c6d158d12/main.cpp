#include <stdio.h>
#include <time.h>

using namespace std;
void wait ( int seconds );
int main ()
{
  time_t start, end;
  double diff;
  time (&start); //useful call
  for (int i=0;i<5;i++) //this loop is useless, just to pass some time.
  {
  printf ("%s\n", ctime(&start));
  wait(1);
  }
  time (&end);//useful call

  diff = difftime(end,start);//this will give you time spent between those two calls.
  printf("difference in seconds=%f",diff); //convert secs as u like
  return 0;
}
void wait ( int seconds )
{
  clock_t endwait;
  endwait = clock () + seconds * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}
}