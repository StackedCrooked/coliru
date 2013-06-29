#!/bin/bash
printf "THIS IS COLIRU\n\n"

get_timestamp_files() {
    find /var/chroot/Archive -name timestamp
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
    cat $1 | sed -e 's,\(.*\),       \1,'
    printf "\n\n"
}

print_entry() {
    printf "=== $2 $(basename $1) ===\n" | sed -e 's,DATE_SEP, ,g'
    print_file "$1/cmd.sh"
    print_file "$1/output"
    print_file "$1/main.cpp"
    printf "\n\n"
}


print_entries() {
    for entry in $(get_entries_by_date) ; do
        export TS="$(echo $entry | cut -d '_' -f1)"
        export DATE="$(convert_epoch_to_readable_format $TS)"
        export DIR="$(echo $entry | cut -d '_' -f2)"
        export BASE_DIR="$(basename $DIR)"
        print_entry $DIR $DATE
    done
}


# If we have a recent cache then use that.
# Otherwise genereate the cache.
HOUR_INDEX="$(($(date +%s) / 3600))"
CACHE_FILE="/tmp/history${HOUR_INDEX}"
PART_FILE="${CACHE_FILE}.part"


{ [ -f "$CACHE_FILE" ] && {
    printf "$CACHE_FILE does exist. Returning cached results.\n\n"
    cat $CACHE_FILE
    exit
} ; } || echo "$CACHE_FILE does not exist."


{ [ -f $PART_FILE ] && {
    printf "$PART_FILE does exist. Returning partial results.\n\n"
    cat $PART_FILE
    exit
} ; } || echo "$PART_FILE does not exist."

echo "Generating history cache now. Refresh to see partial results."
{ print_entries > $PART_FILE && mv $PART_FILE $CACHE_FILE ; } & disown
