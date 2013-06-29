#!/bin/bash
#set -x

get_timestamp_files() {
    find /var/chroot/Archive -name timestamp | head -n100
}

get_entries_by_date() {
    {
        for entry in $(get_timestamp_files) ; do
            printf "$(cat $entry)_$(dirname $entry)\n"
        done
    } | sort -n -r | head -n100
}

convert_epoch_to_readable_format() {
    echo "$(date -d @${1} +"%Y-%m-%d %H:%M" | sed 's, ,DATE_SEP,g')"
}

print_file() {
    printf "$(basename $1):\n"
    cat $1 | sed -e 's,\(.*\),       \1,'
    printf "\n\n"
}

print_entry() {
    printf "=== $2 ===\n" | sed -e 's,DATE_SEP, ,g'
    print_file "$1/cmd.sh"
    print_file "$1/main.cpp"
    print_file "$1/output"
}



for entry in $(get_entries_by_date) ; do
    export TS="$(echo $entry | cut -d '_' -f1)"
    export DATE="$(convert_epoch_to_readable_format $TS)"
    export DIR="$(echo $entry | cut -d '_' -f2)"
    export BASE_DIR="$(basename $DIR)"
    #echo "$TS $DATE"
    print_entry $DIR $DATE
done

exit
for dir in $(ls /var/chroot/Archive | grep '-' | sort -n -r | head -n100) ; do
    for file in $(find /var/chroot/Archive/$dir -type f | grep -v '\.svn') ; do
        echo $file
        EPOCH="$(($(basename $(dirname $file)) / 1000000000))"
        echo $EPOCH
        #printf "======== $file ========\n" 
        #cat $file
        #printf "\n\n"
    done 
done
