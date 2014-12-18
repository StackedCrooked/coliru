echo stdlibc++ > stdlibc++ && g++ -std=c++11 main.cpp && ./a.out >>stdlibc++
echo libc++ > libc++ && clang++ -std=c++11 -stdlib=libc++ main.cpp && ./a.out >>libc++
echo "Results:" ; diff -y -t stdlibc++ libc++