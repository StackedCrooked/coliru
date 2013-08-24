encoded_command="$(echo $@ | base64)"
cache_dir="${HOME}/.Cache.sh"
mkdir -p ${cache_dir}
cache_file="${cache_dir}/${encoded_command}"
[ -f ${cache_file} ] || {
    echo "$($@)" >$cache_file
}
cat ${cache_file}
