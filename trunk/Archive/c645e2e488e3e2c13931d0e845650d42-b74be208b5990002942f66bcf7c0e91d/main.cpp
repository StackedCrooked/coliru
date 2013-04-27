printf "Number of submissions: $(find /Archive -name main.cpp | wc -l)\n"
printf "Size of Archive: $(du -sh /Archive | perl -p -e 's,(\w+).*,\1,')\n"

for i in `seq 50` ; do
    printf "\n====================\n"
    printf "=== Random entry ===\n"
    printf "====================\n"
    ls /Archive | head -n$(($RANDOM % $(find /Archive -name main.cpp | wc -l))) | tail -n1 | xargs -I {} cat /Archive/{}/main.cpp
done

