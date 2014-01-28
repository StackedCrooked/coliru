(base64 -d | xzcat | cpio -i) <<DEMO_FILES
/Td6WFoAAATm1rRGAgAhARwAAAAQz1jM4An/AoJdAGOcPkAEKASvyP1Yi44psrOYzcEhZ0VIVPI7
Jj2BLpcUgAf19RT/nHpJRWp7BHKqwQ4DEMA6pOwrJNyPqRyo46eY5hXGYfawNTNxQ/u04m5hgpkp
m2FWhIIshI8QZBHAUfzrI7f/83eD2YEQNwdRyGp+7M2ZB/gmgHbAIhSq1jGy73xXBOpeVv+8SUuE
GPE3+MRWFrYd1PdPRMveA6HSO5/PaT8KEWb1dA9Y3GwBG0lhZnLRUvLHykrjysrEYbBi2Q25INam
AZzSfemUFSyJHsAL01SFgNXEOmQ5RTIQ2yUksE+w3E7sx8OKEeh4f2JPvaVmrUwkGMr8Mm57rE7D
7ycxGmgiDmUNXmgQxhk74bO1KJhwfrPqvAzog+2tr6lon8hk/Hh9MJxIBE1dU8Sl8ABzbXTHLYFZ
RH07iheMfWE6ecybJ1XpnQuBu3IXTHHwiKCHTos8oe9pVspHZ7LO7/W5j+DEDegFGGw6d1qQOPty
UPaGbQrjXrop+GRWwHeUvfjm33s716NYncSfvtfpuZZuLioqjS3tofyj2q/I+cigijywiLXmyoEz
BFNfA7HGUBUTnaGiVLzuNH0HiSdylr7V5ln1DmgpGo2mlEJaMaazaiq/ta7+mOrRIebu/THMjOLP
R4xO83jYxUuld/yNoe+9P4Yx8u19VbIVyk8UvyWGBdPSFlscjgYF6tO30403iEus90/1pYb+S5Af
6esxSSMslPXr9st5XZq7lkr6dqzTxaiapBG+JTTsRgs3F/TbS03FqFeEu+qoCcE0UvrxfkPiQuon
YTCYOI8+jmA/qrgrwPxWPhk45ki/ahUPj0ToL0Br2vo+FntGCqXBe2FGwp/VwAAAAKv2tGVnAbOh
AAGeBYAUAAAJka/ascRn+wIAAAAABFla
DEMO_FILES

g++ -std=c++11 -Wl,-rpath -Wl,. -g -c -Wall -fPIC base.cpp -o base.o
g++ -std=c++11 -Wl,-rpath -Wl,. -shared -o libbase.so base.o -lc
g++ -std=c++11 -Wl,-rpath -Wl,. -g -c -Wall -fPIC derived.cpp -o derived.o
g++ -std=c++11 -Wl,-rpath -Wl,. -shared -o libderived.so derived.o -lc
g++ -std=c++11 -Wl,-rpath -Wl,. main.cpp -lbase -lderived -o main -L . -lboost_serialization

./main && cat test.txt