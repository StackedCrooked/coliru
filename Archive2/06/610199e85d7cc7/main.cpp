#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
     
typedef struct Options_s {
  char *test_file;
} Options;

int parse_options(int argc, char **argv, Options* options)
{
  int c;
     
  opterr = 0;
       
#define FILE_NAME_DEFAULT "test"
       
  options->test_file = FILE_NAME_DEFAULT;
     
  while ((c = getopt (argc, argv, "f:")) != -1)
    switch (c)
      {
 case 'f':
   options->test_file = optarg;
   break;
 case '?':
   if (optopt == 'f')
     fprintf (stderr, "Option -%c requires an argument.\n", optopt);
   else if (isprint (optopt))
     fprintf (stderr, "Unknown option `-%c'.\n", optopt);
   else
     fprintf (stderr,
    "Unknown option character `\\x%x'.\n",
    optopt);
   return 1;
 default:
   abort ();
}
  return 0;
}

 int
   main (int argc, char **argv)
 {

       
  Options options; 
       
  parse_options(argc, argv, &options);
     
  printf ("f = %s\n",
    options.test_file);

  return 0;
}