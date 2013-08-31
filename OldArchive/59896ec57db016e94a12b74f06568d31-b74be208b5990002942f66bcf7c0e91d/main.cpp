

hash_file() {
    md5sum $1 | cut -d' ' -f1
}

hash_string() {
    echo $1 | md5sum | cut -d' ' -f1
}



before_truncate="$(hash_file cmd.sh)$(hash_file main.cpp)"
after_truncate="$(hash_string ${before_truncate})"

echo "before_truncate: ${before_truncate}"
echo "after_truncate: ${after_truncate}"
