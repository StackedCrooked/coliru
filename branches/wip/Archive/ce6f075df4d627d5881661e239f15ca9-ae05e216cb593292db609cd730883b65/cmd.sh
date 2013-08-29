clang++ -std=c++11 -O0 main.cpp && ./a.out<<HERE
where currency like "GBP|USD" set logging = 1, logfile = "myfile"
where not status = "ok" print ident, errorMessage
where status = "ok" or not currency like "GBP|USD" print ident, errorMessage
where status = "\"special\"" set logfile = "C:\\path\\to\\logfile.txt"
HERE