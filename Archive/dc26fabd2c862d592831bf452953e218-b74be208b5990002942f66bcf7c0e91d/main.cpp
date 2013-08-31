printf "Number of submissions: $(find /Archive -name main.cpp | wc -l)\n"
printf "Size of Archive: $(du -sh /Archive | perl -p -e 's,(\w+).*,\1,')\n"

echo "Random entry:"
ls /Archive | head -n$(($RANDOM % $(find /Archive -name main.cpp | wc -l))) | tail -n1 | xargs -I {} cat /Archive/{}/main.cpp

