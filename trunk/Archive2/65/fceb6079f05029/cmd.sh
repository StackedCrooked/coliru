#title Macro for generating a serializable record. (TODO: don't break intellisense!) (Tags: protobuf, rpc, communication, strong typedef)
g++ -std=c++11 -O0 -Wall -E -o - main.cpp -isystem /opt/local/include | grep 'struct Stats2\|main()' >pp.cpp
printf "#include <boost/operators.hpp>\n#include <boost/preprocessor.hpp>\n#include <cstdint>\n" >pp2.cpp
cat pp.cpp  | perl -pe 's,},\n}\n\n,g; s,\s+;,;,g' >>pp2.cpp
astyle --style=allman -c <pp2.cpp >pp3.cpp
printf "newlines=LF\nindent_columns=4\nindent_with_tabs=0\n" >.uncrustify-config && uncrustify -f pp3.cpp -l CPP -c .uncrustify-config -o pp4.cpp
g++ -std=c++11 pp4.cpp && echo "Compilation of preprocessed file succeeded:" && cat pp4.cpp