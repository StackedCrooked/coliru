#!/bin/bash
cache_dir="${HOME}/.Cache.sh"
mkdir -p "${cache_dir}"
cache_file="${cache_dir}/$(echo $@ | base64)"
[ -f "${cache_file}" ] || {
    echo "$($@)" >"$cache_file"
}
cat "${cache_file}"
