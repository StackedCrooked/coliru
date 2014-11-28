ccache-3.2 $ time make
gcc -DHAVE_CONFIG_H  -DSYSCONFDIR=/usr/local/etc -I. -I.  -g -O2 -Wall -W -c -o main.o main.c
gcc -DHAVE_CONFIG_H  -DSYSCONFDIR=/usr/local/etc -I. -I.  -g -O2 -Wall -W -c -o ccache.o ccache.c
gcc -DHAVE_CONFIG_H  -DSYSCONFDIR=/usr/local/etc -I. -I.  -g -O2 -Wall -W -c -o mdfour.o mdfour.c
gcc -DHAVE_CONFIG_H  -DSYSCONFDIR=/usr/local/etc -I. -I.  -g -O2 -Wall -W -c -o hash.o hash.c
gcc -DHAVE_CONFIG_H  -DSYSCONFDIR=/usr/local/etc -I. -I.  -g -O2 -Wall -W -c -o execute.o execute.c
gcc -DHAVE_CONFIG_H  -DSYSCONFDIR=/usr/local/etc -I. -I.  -g -O2 -Wall -W -c -o util.o util.c
gcc -DHAVE_CONFIG_H  -DSYSCONFDIR=/usr/local/etc -I. -I.  -g -O2 -Wall -W -c -o args.o args.c
gcc -DHAVE_CONFIG_H  -DSYSCONFDIR=/usr/local/etc -I. -I.  -g -O2 -Wall -W -c -o stats.o stats.c
gcc -DHAVE_CONFIG_H  -DSYSCONFDIR=/usr/local/etc -I. -I.  -g -O2 -Wall -W -c -o version.o version.c
gcc -DHAVE_CONFIG_H  -DSYSCONFDIR=/usr/local/etc -I. -I.  -g -O2 -Wall -W -c -o cleanup.o cleanup.c
gcc -DHAVE_CONFIG_H  -DSYSCONFDIR=/usr/local/etc -I. -I.  -g -O2 -Wall -W -c -o snprintf.o snprintf.c
gcc -DHAVE_CONFIG_H  -DSYSCONFDIR=/usr/local/etc -I. -I.  -g -O2 -Wall -W -c -o unify.o unify.c
gcc -DHAVE_CONFIG_H  -DSYSCONFDIR=/usr/local/etc -I. -I.  -g -O2 -Wall -W -c -o manifest.o manifest.c
gcc -DHAVE_CONFIG_H  -DSYSCONFDIR=/usr/local/etc -I. -I.  -g -O2 -Wall -W -c -o hashtable.o hashtable.c
gcc -DHAVE_CONFIG_H  -DSYSCONFDIR=/usr/local/etc -I. -I.  -g -O2 -Wall -W -c -o hashtable_itr.o hashtable_itr.c
gcc -DHAVE_CONFIG_H  -DSYSCONFDIR=/usr/local/etc -I. -I.  -g -O2 -Wall -W -c -o murmurhashneutral2.o murmurhashneutral2.c
gcc -DHAVE_CONFIG_H  -DSYSCONFDIR=/usr/local/etc -I. -I.  -g -O2 -Wall -W -c -o hashutil.o hashutil.c
gcc -DHAVE_CONFIG_H  -DSYSCONFDIR=/usr/local/etc -I. -I.  -g -O2 -Wall -W -c -o getopt_long.o getopt_long.c
gcc -DHAVE_CONFIG_H  -DSYSCONFDIR=/usr/local/etc -I. -I.  -g -O2 -Wall -W -c -o exitfn.o exitfn.c
gcc -DHAVE_CONFIG_H  -DSYSCONFDIR=/usr/local/etc -I. -I.  -g -O2 -Wall -W -c -o lockfile.o lockfile.c
gcc -DHAVE_CONFIG_H  -DSYSCONFDIR=/usr/local/etc -I. -I.  -g -O2 -Wall -W -c -o counters.o counters.c
gcc -DHAVE_CONFIG_H  -DSYSCONFDIR=/usr/local/etc -I. -I.  -g -O2 -Wall -W -c -o language.o language.c
gcc -DHAVE_CONFIG_H  -DSYSCONFDIR=/usr/local/etc -I. -I.  -g -O2 -Wall -W -c -o compopt.o compopt.c
gcc -DHAVE_CONFIG_H  -DSYSCONFDIR=/usr/local/etc -I. -I.  -g -O2 -Wall -W -c -o conf.o conf.c
gcc -g -O2 -Wall -W -o ccache main.o ccache.o mdfour.o hash.o execute.o util.o args.o stats.o version.o cleanup.o snprintf.o unify.o manifest.o hashtable.o hashtable_itr.o murmurhashneutral2.o hashutil.o getopt_long.o exitfn.o lockfile.o counters.o language.o compopt.o conf.o -lz   

real    0m1.520s
user    0m1.094s
sys	0m0.366s