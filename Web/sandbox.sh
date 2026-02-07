#!/bin/bash
echo $$

set -e
source coliru_env.source

# check if INPUT_FILES_DIR is set.
[ "$INPUT_FILES_DIR" == "" ] && { echo "INPUT_FILES_DIR not set." 1>&2 ; exit 1 ; }


# get the id (a on hash of main.cpp and cmd.sh)
id="$(./hash.sh)"

# search for previous result in the compile cache
[ -d ${COLIRU_COMPILE_CACHE}/${id} ] && {
    cat "${COLIRU_COMPILE_CACHE}/${id}/output" 2>/dev/null && exit

    # In case the 'output' file was not found.
    rm -rf "${COLIRU_COMPILE_CACHE}/${id}"
}

# search for previous output in the new archive
# pathifiedId puts a slash after the first two characters ("abcdefgh..." => "ab/cdefgh...")
pathifiedId="$(./pathify-id.sh ${id})"
[ -d "${COLIRU_ARCHIVE2}/${pathifiedId}" ] && {
    cat "${COLIRU_ARCHIVE2}/${pathifiedId}/output" && exit
}

# search for previous result in the old archive
[ -d ${COLIRU_ARCHIVE}/${id} ] && {
    cat "${COLIRU_ARCHIVE}/${id}/output" && exit
}

# no previous result found => compile it and print the output
mkdir -p ${COLIRU_COMPILE_CACHE}/${id}

# Avoid process-substitution tee here because failed runner startups can leave
# defunct tee children behind. A plain pipeline is reaped correctly by bash.
./build_and_run.sh 2>&1 | tee "${COLIRU_COMPILE_CACHE}/${id}/output"
