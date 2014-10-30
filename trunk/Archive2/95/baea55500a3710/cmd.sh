#input size / compressed size = compression ratio
for i in {1..1000} ; do c="$(head -c${i} /usr/bin/vim | gzip | wc -c)" ; echo "$i / $c = $( echo "scale=2; $i/$c" | bc)" ; done | column -t