mv main.cpp main.hs
ghc --make -O2 main.hs -o hello && ./hello