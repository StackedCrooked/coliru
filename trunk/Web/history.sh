#!/bin/bash
cd $(dirname $0)
printf "THIS IS COLIRU\n\n"

get_timestamp_files() {
    find /var/chroot/Archive2 -name timestamp
}

get_entries_by_date() {
    {
        for entry in $(get_timestamp_files) ; do
            printf "$(cat $entry)_$(dirname $entry)\n"
        done
    } | sort -n -r | head -n 100
}

convert_epoch_to_readable_format() {
    echo "$(date -d @${1} +"%Y-%m-%d %H:%M" | sed 's, ,DATE_SEP,g')"
}

print_file() {
    CHARACTERS=$(cat $1 | wc -c)
    [ $CHARACTERS -lt 8000 ] || { printf "$(basename $1): too big ($CHARACTERS characters)\n\n" ; return ; }
    printf "$(basename $1):\n"
    cat $1 | sed -e 's,\(.*\),  \1,'
    printf "\n\n"
}

print_entry() {
    printf "=== $2 $(basename $1) ===\n" | sed -e 's,DATE_SEP, ,g'
    print_file "$1/main.cpp"
    print_file "$1/output"
    print_file "$1/cmd.sh"
    printf "\n\n"
}


print_entries() {
    for entry in $(get_entries_by_date) ; do
        export TS="$(echo $entry | cut -d '_' -f1)"
        export DATE="$(convert_epoch_to_readable_format $TS)"
        export DIR="$(echo $entry | cut -d '_' -f2)"
        print_entry $DIR $DATE
    done
}


# If we have a recent cache then use that.
# Otherwise genereate the cache.
HOUR_INDEX="$(($(date +%s) / 3600))"
HISTORY_FILE="/tmp/history${HOUR_INDEX}"
PART_FILE="${HISTORY_FILE}.part"


#
# START OF PROGRAM
#

# Return cached results if available.
[ -f "$HISTORY_FILE" ] && {
    cat $HISTORY_FILE
    exit
}


export PREVIOUS_RESULTS="$({ ls /tmp/history* -t1 | grep -v part |  head -n1 ; } 2>/dev/null)"
if [ "${PREVIOUS_RESULTS}" != "" ] ; then
    cat ${PREVIOUS_RESULTS}
fi

# Presence of the part file indicates that another process is already working on it.
[ -f $PART_FILE ] && {
    echo "Partial results. Refresh later to see more."
    cat $PART_FILE
    exit
}

echo "Generating history for the first time. This may take a few minutes. Refresh a little bit later to see the results."

{
    echo "Note: generating results. refresh to see more."
    print_entries > $PART_FILE
    mv $PART_FILE $HISTORY_FILE
} & disown
