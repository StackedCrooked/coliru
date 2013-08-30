#!/bin/bash
source coliru_env.source
[ "$INPUT_FILES_DIR" == "" ] && { echo "INPUT_FILES_DIR is not set." 1>&2 ; exit 1 ; }
[ "$INPUT_FILES_DIR" == "." ] && { echo "INPUT_FILES_DIR is jsut a dot." 1>&2 ; exit 1 ; }

export INPUT_FILES_DIR

# Make the archive id
id="$(./hash.sh)"

# This is the only return 
echo "${id}"


# If the id already existed then simply return.
# We don't have to compile anymore.
if [ -d "${COLIRU_ARCHIVE}/${id}" ] ; then
    exit
fi

# The archive directory for the ide.
export dir="${COLIRU_ARCHIVE}/${id}"
mkdir ${dir}

chmod 755 ${INPUT_FILES_DIR}/cmd.sh
cat ${INPUT_FILES_DIR}/main.cpp > ${dir}/main.cpp
cat ${INPUT_FILES_DIR}/cmd.sh > ${dir}/cmd.sh
date '+%s' > ${dir}/timestamp


# Build and run it.
./build_and_run.sh >${dir}/output 2>&1

# Add the results to svn
svn add ${dir} >/dev/null 2>&1 & disown
