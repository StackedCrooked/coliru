count_files () 
{ 
    locate "$1" | grep -i "\.$1$" | wc -l
}

count_files cpp
   28216
count_files h
   50356
count_files rb
    6783
count_files py
   12197
count_files tcl
    1357
count_files m
    1240
count_files txt
    5062
