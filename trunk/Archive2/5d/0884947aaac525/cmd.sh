set -x;
# Create a Python Script embed.py
cat >embed.py <<INPUT
from ctypes import *
class SimulinkBus(Structure):
    _fields_ = [ ("a", c_int), ("b", c_char), ("c", c_float), ("d", c_double), ("e", c_char_p), ("arr", c_int*4) ]
  
def Logic( Signal ):
    return  Signal.a*2 + Signal.c 
    
def main( *args,**kwargs ):
    for a in args:
       print (a)
    for k,v in kwargs.iteritems():
         print ("%s = %s" % (k, v))
    Signal = cast(c_char_p(kwargs['SimulinkBus']), POINTER(SimulinkBus )).contents
    print (Signal.a, Signal.b, Signal.c, Signal.d, Signal.e )
    for i in range(4):
        print ( Signal.arr[i] )
        Signal.arr[i] *= 2
    Signal.c = Logic( Signal )
    return Signal
INPUT

# Compile the C code
gcc -o test -O2 -Wall -Wextra main.cpp -I /usr/include/python2.7 -lpython2.7
# Run C code
./test embed main