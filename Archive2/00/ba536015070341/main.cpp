#!/bin/bash

echo "Hello World!" 
#!/bin/bash
shopt -s nullglob
if [ -d logs ]; then echo Error; exit 1  #there is a dir named logs
else mkdir logs 
fi

sum=0
num_of_lines=`wc -l < ${1}`  #counting lines in given file 

i=1

while [[ $i -le $num_of_lines ]]; do 

var=`head -$i "$1"|tail -1|wc -c`
if (($var==1)); then
(( i=i-1 ))
break
fi

    echo $i: `sed -n "${i}p" ${1} | cut -d"@" -f1`					   # prints line_num, then 
	  # prints only the first (f1) part of this line, until '@'
	  
	lin=`head -$i "$1" |tail -1`
	echo "$lin">temp.txt 
	h[1]=`cut -d"@" -f2 temp.txt`
	h[2]=`cut -d"@" -f3 temp.txt`
	h[3]=`cut -d"@" -f4 temp.txt`
	
	testCompile logs/"$i".compile "${h[1]}"
	if ((  $?==0 )); then (( sum=sum+1 )) ; fi
	testInOut logs/"$i".inout "${h[1]}" "${h[2]}" "${h[3]}"
	if ((  $?==0 )); then (( sum=sum+1 )) ; fi
	testMem logs/"$i".memory "${h[1]}" "${h[2]}"
	if ((  $?==0 )); then (( sum=sum+1 )) ; fi  
	  
rm -f temp.txt

	((i = i + 1))
done

(( i=i*3 ))
echo Passed "$sum" of "$i" tests
exit 0