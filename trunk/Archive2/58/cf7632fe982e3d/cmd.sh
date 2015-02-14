mv main.cpp Main.hs && cp /Archive2/c1/0d123d5300e58c/main.cpp Fix.hs \
&& ghc --make Main.hs && ./Main "(a and b) xor ((c and d) or (a and b))"