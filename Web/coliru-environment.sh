#!/bin/bash
COLIRU=${COLIRU:-${HOME}/coliru}
COLIRU_ARCHIVE=${COLIRU_ARCHIVE:-${COLIRU}/Archive}
echo "Overridable variables related to COLIRU:"
set | grep COLIRU
