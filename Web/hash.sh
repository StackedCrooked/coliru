#!/bin/bash
[ "$INPUT_FILES_DIR" == "" ] && {
    echo "INPUT_FILES_DIR is not set." 1>&2
    exit 1
}

[ -d "$INPUT_FILES_DIR" ] || {
    echo "INPUT_FILES_DIR=$INPUT_FILES_DIR which is not an existing directory." 1>&2
    exit 1
}

# start a subshell in order to restore
# the current directory when it exits
# increment cache_invalidator to force invalidating all caches
(
    cd "${INPUT_FILES_DIR}"
    echo cache_invalidator=4

    # Wide requires boost lib in /usr/local/lib
    LD_LIBRARY_PATH="/usr/local/lib" /usr/local/bin/Wide/CLI --version

    type g++ && g++ --version
    type clang++ && clang++ --version
    cat main.cpp
    cat cmd.sh
) 2>&1 | shasum | awk '{print $1}' | cut -c -16
