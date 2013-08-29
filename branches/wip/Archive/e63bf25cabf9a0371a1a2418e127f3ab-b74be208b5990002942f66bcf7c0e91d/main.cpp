
next_id() {
    prev=$(ls -t | head -1)
    echo $(($prev + 1))
}

grap_unique_id() {
    id=$(next_id)
    while ! mkdir ${id} 2>/dev/null ; do
        echo "$1 failed to grab ${id}"
        id=$(($id + 1))
    done
    echo "$1 grabbed ${id}"
}


echo "Staring the competition."
touch 0

for i in $(seq 10) ; do
    grap_unique_id "job_${i}" &
done


