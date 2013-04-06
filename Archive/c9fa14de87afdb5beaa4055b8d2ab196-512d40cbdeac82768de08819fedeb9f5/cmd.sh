find /Archive -name timestamp | xargs grep . | perl -p -e 's,(.+?):(.+),\2 \1,g' | sort -r -n | cut -d ' ' -f2 | xargs -I {} dirname {} | xargs -I {} echo "{}/main.cpp" | xargs -I {} bash -c "echo '================================================================================' ; cat {} ; echo"


