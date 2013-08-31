# Shows most recent coliru posts
POSTS="$(ls -t /Archive/*/timestamp | xargs -I {} dirname {} | xargs -I {} basename {})"
for p in $POSTS ; do 
    echo -n $(date -d @$(cat /Archive/$p/timestamp) +"%Y-%m-%d %H:%M:%S") ; echo ": http://coliru.stacked-crooked.com/view?=$p"
done