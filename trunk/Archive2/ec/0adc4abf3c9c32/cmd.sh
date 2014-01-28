(base64 -d | xzcat | cpio -i) <<DEMO_FILES
/Td6WFoAAATm1rRGAgAhARwAAAAQz1jM4An/An1dAGOcPkAEKASvyP1Yi44psrOYzcEhZ0VIVPI7
Jj2BLpcUgAf19RT/nHpJRWp7BHKqwQ4DEMA6pOwrJNyPqRyo46eY5hXGYfawNTNxQ/u04m5hgpkp
m2FWhIIshI8QZBHAUfzrI7f/83eD2YEQNwdRyGp+7M2ZB/gmgHbAIhSq1jGy73xXBOpeVv+8SUuE
GPE3+MRWFrYd1PdPRMveA6HSO5/PaT8KEWb1dA9Y3GwBG0lhZnLRUvLHykrjysrEYbBi2Q25INam
AZzSfemUFSyJHsAL01SFgNXEOmQ5RTIQ2yUksE+w3E7sx8OKEeh4f2JPvaVmrUwkGMr8Mm57rE7D
7yReDT1TRuObWUoIeWqeIF0kPalA8PmFqSdBq5dNwTF7ylhLyDoJOudYaZPOXHQL85zpgu+WXXuv
oaLomi6ov2pjD8+F251WAbDLthA0cdO6hqYK9tHi1lzS94U3HoQkxxDnAoZdBtgSYr7VPsm4Dbd8
zLn9mjHK6Zht+yFT3sEsCnDnbrVWbSbslK/Buang/0XQBC/Z/L7A6oQKjTaVHPvApAfP/RGDhCwS
Yh3VaQEw33DkX1//BXPx2RdPIaHdrXPp/f1BHDyxre1R6c38xJcXDFlSKEi4220GqPQkUx2RwbOH
44zalNr52jo2RCpjz82BB5coXeoRCEiN27PhesI3VdyY9TXns8fNt693pmK4ABenwm8Tc038xaM+
KX53v37lsN/N9ySZIZBYhXzQ8VFaWHyEuNWyY00DR2NcFmtUhJloM7hv6pgOtXb7FZ4NEEbtwOeK
aoP8nR+a1qLIfEZsvtcyC0/xwHQKDB1ghFd7rttDqbT696tHSP5N2gAAAAAABcEdXMBL4PsAAZkF
gBQAALGhqsexxGf7AgAAAAAEWVo=
DEMO_FILES

g++ -c -Wall -fPIC base.cpp -o base.o
g++ -shared -o libbase.so base.o -lc
g++ -c -Wall -fPIC derived.cpp -o derived.o
g++ -shared -o libderived.so derived.o -lc
g++ -Wl,-rpath -Wl,. main.cpp -lbase -lderived -o main -L . -lboost_serialization

./main && cat test.txt