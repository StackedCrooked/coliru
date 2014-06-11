#!/bin/bash
[ "$INPUT_FILES_DIR" == "" ] && {
    echo "INPUT_FILES_DIR is not set." 1>&2
    exit 1
}

# start a subshell in order to restore
# the current directory when it exits
(
    cd ${INPUT_FILES_DIR}
    cat *
    type g++ && g++ --version
    type clang++ && clang++ --version
    /usr/local/bin/Wide/CLI --version
) 2>&1 | shasum | awk '{print $1}' | cut -c -16
