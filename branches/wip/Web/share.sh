#!/bin/bash
source coliru_env.source
[ "$INPUT_FILES_DIR" == "" ] && { echo "INPUT_FILES_DIR is not set." 1>&2 ; exit 1 ; }

export INPUT_FILES_DIR

# Make the archive id
id="$(./hash.sh)"
path="$(./id2path.sh ${id})"
[ -d "${path}" ] && {
    echo "${id}" | sed 's,/,,'
    exit
}

# The first line of output determines the archive id.
echo "${id}" | sed 's,/,,'
{
    exec 1> >(logger -t "$0 stdout")
    exec 2> >(logger -t "$0 stderr")
    set -x

    # If the id already existed then simply return.
    # We don't have to compile anymore.
    [ -d "${COLIRU_ARCHIVE}/${id}" ] && exit
    [ -d "${COLIRU_ARCHIVE_RECENT}/${id}" ] && exit

    # The archive directory for the ide.
    mkdir -p ${path}

    chmod 755 ${INPUT_FILES_DIR}/cmd.sh
    cat ${INPUT_FILES_DIR}/main.cpp > ${path}/main.cpp
    cat ${INPUT_FILES_DIR}/cmd.sh > ${path}/cmd.sh
    date '+%s' > ${path}/timestamp

    # Build and run it.
    ./build_and_run.sh >${path}/output 2>&1

    # Add to svn
    svn add ${path}
}
