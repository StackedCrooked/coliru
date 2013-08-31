$ ls
crap.cc  SConstruct
$ cat crap.cc
int main() {}
$ cat SConstruct
Program("crap.cc")
$ scons
scons: Reading SConscript files ...
scons: done reading SConscript files.
scons: Building targets ...
g++ -o crap.o -c crap.cc
g++ -o crap crap.o
scons: done building targets.
$ scons -c
scons: Reading SConscript files ...
scons: done reading SConscript files.
scons: Cleaning targets ...
Removed crap.o
Removed crap
scons: done cleaning targets.
$ make crap
g++     crap.cc   -o crap
$
