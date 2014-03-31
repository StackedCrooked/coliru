#!/bin/bash
source coliru_env.source
[ "$INPUT_FILES_DIR" == "" ] && { echo "INPUT_FILES_DIR is not set." 1>&2 ; exit 1 ; }

export INPUT_FILES_DIR

# Make the archive id
id="$(./hash.sh)"
path="$(./id2path.sh ${id})"

# print the archive id to stdout
# this is used for share URL
echo "${id}" | sed 's,/,,'

# block to prevent accidental writes to stdout or stderr
{
    # redirect all output to logger because we don't 
    # want to pollute the outputted id with other stuff
    source logger.source

    # if archive already exists then we can exit
    [ -d "${path}" ] && exit

    # create the archive directory and add the files
    # an empty output file is also added here
    mkdir -p "${path}"
    cat ${INPUT_FILES_DIR}/main.cpp > ${path}/main.cpp
    cat ${INPUT_FILES_DIR}/cmd.sh > ${path}/cmd.sh
    echo > ${path}/output
    date '+%s' > ${path}/timestamp

    # perform svn add BEFORE running the script
    # because we can get killed during run
    # actual svn commit will be performed by a 
    # maintenance script 
    svn add --force ${path}

    # use output of compile cache if available
    # note that this does not remove the need
    # for svn add. 
    [ -d ${COLIRU_COMPILE_ARCHIVE}/${id} ] && {
        cat "${COLIRU_COMPILE_ARCHIVE}/${id}/output" >"${path}/output"
        exit
    }

    # run program, writing to output file in the archive
    ./build_and_run.sh >${path}/output 2>&1

} >/dev/null 2>&1

