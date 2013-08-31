mv main.cpp main.hs
ghc --make -O2 main.cpp -o hello && ./hello