g++ -DOPTIMIZE_BRANCH=1 -O2 -Wall -pedantic -S -masm=intel main.cpp -o - | c++filt > optimize_branch
g++ -DOPTIMIZE_BRANCH=0 -O2 -Wall -pedantic -S -masm=intel main.cpp -o - | c++filt > no_optimize_branch
diff -y optimize_branch no_optimize_branch