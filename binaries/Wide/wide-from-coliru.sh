#!/bin/bash

# This is a helper script for invoking the Wide compiler from Coliru.


# Invoke the CLI with the user parameters.
/usr/local/bin/Wide/CLI --stdlib="/usr/local/bin/Wide/WideLibrary" "$@"
