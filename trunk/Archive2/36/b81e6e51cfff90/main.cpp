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
           int aflag = 0;
       int bflag = 0;
       char *cvalue = NULL;
       int index;
       int c;
     
       opterr = 0;
       
           #define FILE_NAME_DEFAULT "test"
       
       options->test_file = FILE_NAME_DEFAULT;
     
       while ((c = getopt (argc, argv, "abc:")) != -1)
         switch (c)
           {
           case 'a':
             aflag = 1;
             break;
           case 'b':
             bflag = 1;
             break;
           case 'c':
             options->test_file = optarg;
             break;
           case '?':
             if (optopt == 'c')
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
}

     int
     main (int argc, char **argv)
     {

       
       Options options; 
       
       parse_options(argc, argv, &options);
     
       printf ("cvalue = %s\n",
               options.test_file);

       return 0;
     }