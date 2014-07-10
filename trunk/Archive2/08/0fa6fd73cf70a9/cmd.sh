cat > input.txt <<INPUT; g++ -std=c++03 -Os -Wall -pedantic main.cpp -lboost_regex && ./a.out <<REGEX.TXT
192.168.1.9 - - [20/Apr/2014:07:46:19 -0400] "GET /dvwa/favicon.ico HTTP/1.1" 200 1406 "-" "Mozilla/5.0 (Windows NT 6.3; WOW64; rv:28.0) Gecko/20100101 Firefox/28.0"
INPUT
((?<destination_ip>\S+)?)(\s[+-]){2} \[(?<timestamp>\d{2}/\w{3}/\d{4}:\d{2}:\d{2}:\d{2})\s+[+-]\d{4}\] "(?<referer_uri>.*)"
REGEX.TXT