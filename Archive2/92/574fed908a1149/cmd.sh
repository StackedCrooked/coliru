set -x;
cat >main.py <<INPUT
def foo(*args, **kwargs):
   for a in args:
       print a
   for k,v in kwargs.iteritems():
       print "%s = %s" % (k, v)
   return 42
INPUT

gcc -O2 -Wall main.cpp -I /usr/include/python2.7 -lpython2.7 

./a.out main foo 1 2 3