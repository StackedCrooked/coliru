#!/bin/bash

# This is a helper script for invoking the Wide compiler from Coliru.

# Wide/CLI tries to find WideLibrary in the working directory of the caller.		
ln -s "$(dirname $0)/Wide/WideLibrary" .

# Tell the system to look inside /usr/local/lib for libboost_program_options.so.1.54.0
export LD_LIBRARY_PATH="/usr/local/lib:${LD_LIBRARY_PATH}"

# Invoke the CLI with the user parameters.
/usr/local/bin/Wide/CLI --stdlib="/usr/local/bin/Wide/WideLibrary" "$@"
