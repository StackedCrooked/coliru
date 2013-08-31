{
    echo FileName FileSize NumberOfCharacters 
    for f in $(find /Archive -type f | head -n100 ) ; do
        echo "$f $(du -sh $f | awk '{print $1}') $(cat $f | wc -c   )"
    done
} | column  -t
