#!/bin/bash

# Add a prefix to each line of stdin.
prefix() {
    local line
    while read line; do printf '%s%s\n' "$1" "$line"; done
}

# Execute each command. Notice the `(' and `)' surrounding the loop body, which starts
# a sub-shell for each iteration. Running in a sub-shell lets us use `trap EXIT' to
# cleanup.
while read command; do (
    # Create FIFOs for the command's stdout and stderr.
    stdout=$(mktemp -u)
    stderr=$(mktemp -u)
    mkfifo "$stdout" "$stderr"

    # Delete the FIFOs when this iteration of the loop finishes. Use `trap' to ensure
    # cleanup happens whether we finish normally or are signalled.
    trap 'rm -f "$stdout" "$stderr"' EXIT

    # Read from the FIFOs in the background, adding the desired prefixes.
    prefix 'O:' < "$stdout" >&1 &
    prefix 'E:' < "$stderr" >&2 &

    # Now execute the command, sending its stdout and stderr to the FIFOs.
    echo "C:$command"
    eval "$command" 1> "$stdout" 2> "$stderr"
    exitcode=$?

    # Wait for the `prefix' processes to finish, then print the exit code.
    wait
    echo "R:$exitcode"
    exit $exitcode
) done