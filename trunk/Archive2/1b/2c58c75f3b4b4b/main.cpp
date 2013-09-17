col1() { awk '{print $1}' ;  }
find_cpp_files() { find /Archive2 -type f -name "main\.cpp" | grep -v '\.svn' | head -n50 ; }
compress() { gzip -9 -cf ; }

print_stats() {
    while read line ; do
        chars="$(wc -c $line | col1)"
        zipped="$(compress <$line |  wc -c | col1)"
        zipped_base64="$(compress <$line | base64)"
        zipped_base64_length="$(echo "$zipped_base64" |  wc -c | col1)"
        file="${line}"
        echo "$file $chars $zipped $zipped_base64_length"
    done 
}


(
    echo "File Size Zipped Zipped+Base64"
    echo "---- ---- ------ -------------"
    find_cpp_files | print_stats | sort -n -r -k3
) | column -t
