
print_0_0() { echo "$1" ; }
print_0_1() { echo Buzz; } 
print_1_0() { echo Fizz; } 
print_1_1() { echo FizzBuzz; } 

for i in $(seq 100) ; do print_$(($i % 3 == 0))_$(($i % 5 == 0)) $i ; done
