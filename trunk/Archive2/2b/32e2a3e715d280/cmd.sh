cat <<HERE >untitled.mtl
# Blender MTL File: 'None'
# Material Count: 2

newmtl None
Ns 0
Ka 0.000000 0.000000 0.000000
Kd 0.8 0.8 0.8
Ks 0.8 0.8 0.8
d 1
illum 2
# Added just for testing:

newmtl Demo
Ns 1
Ka 0.200000 0.300000 0.400000
Kd 0.7 0.7 0.7
Ks 0.9 0.9 0.9
d 42
illum 7
HERE
clang++ -std=c++11 -Os main.cpp -lpthread && ./a.out