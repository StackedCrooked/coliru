#!/bin/bash
set -e

COLIRU_ARCHIVE="../Archive"
COLIRU_ARCHIVE2="../Archive2"

# search in old archive
old="${COLIRU_ARCHIVE}/${1}"
#echo "old: ${old}"
[ -d ${old} ] && { echo "${old}" ; exit ; }

# search in new archive
id="$(./pathify-id.sh $1)"
new="${COLIRU_ARCHIVE2}/${id}"
#echo "new: ${new}"
[ -d "${new}" ] && { echo "${new}" ; exit ; }

