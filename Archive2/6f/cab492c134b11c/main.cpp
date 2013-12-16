// http://man7.org/linux/man-pages/man3/getopt.3.html
int getopt(int argc, char * const argv[],
                  const char *optstring)
{
    argv[1] = argv[0];
    return 0;
}

int main()
{}
