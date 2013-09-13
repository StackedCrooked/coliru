#!/bin/bash
dir="$INPUT_FILES_DIR}"
[ "${dir}" == "" ] && {
    echo "INPUT_FILES_DIR not set." 1>&2 
    exit 1
}

get_text() {
    cat cmd.sh
    [ -f "${dir}/main.cpp" ] && {
        cat main.cpp
        g++ --version
        clang++ --version
    }
}


get_hash() {
    get_text | shasum | cut -d ' ' -f1 | cut -c -16
}

get_hash
