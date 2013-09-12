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

    # The archive directory for the ide.
    mkdir -p ${path}

    # Copy the input files to the archive directory
    chmod 755 ${INPUT_FILES_DIR}/cmd.sh
    cat ${INPUT_FILES_DIR}/main.cpp > ${path}/main.cpp
    cat ${INPUT_FILES_DIR}/cmd.sh > ${path}/cmd.sh

    # Create the output file so that it's added to
    # svn regardless of whether or not the script
    # succeeds or timeouts
    # Note: using echo to ensure creation of text file
    echo > ${path}/output

    # Create the timestamp file.
    date '+%s' > ${path}/timestamp

    # Add the directory and all files (cmd.sh, main.cpp, output, timestamp)
    # to svn. Note: we need to do this before running the script because
    # this process might get killed in case of timeout
    mkdir svn_lock && {
        trap 'rm -f svn_lock' EXIT
        svn add ${1}
    }

    # Use cached output if available otherwise run the program.
    [ -d ${COLIRU_COMPILE_ARCHIVE}/${id} ] && {
        cat "${COLIRU_COMPILE_ARCHIVE}/${id}/output" >"${path}/output"
    } || {
        ./build_and_run.sh >${path}/output 2>&1
    }
}
