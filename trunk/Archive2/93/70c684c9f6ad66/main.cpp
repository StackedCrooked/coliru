

printf "VERSION:\n$(g++ --version)\n\n"
printf "DOUBLE CHECK:\n$(strings $(which g++) | grep '[[:digit:]]\.[[:digit:]]\.[[:digit:]]' | xargs)\n\n"
printf "TRIPLE CHECK:\n$(echo __VERSION__ >a.cpp && g++ -E a.cpp)\n\n"
