find /Archive -name timestamp | xargs grep . | perl -p -e 's,(.+?):(.+),\2 \1,g' | sort -r -n | head -n1 | cut -d ' ' -f2 | xargs -I {} dirname {} | xargs -I {} cat "{}/main.cpp"
