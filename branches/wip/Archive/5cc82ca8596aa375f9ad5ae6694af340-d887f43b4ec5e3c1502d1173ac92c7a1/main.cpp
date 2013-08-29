HEADER='<html><body>'
FOOTER='</body></html>'

for f in `ls -t /Archive | head -n10` ; do 
    echo "<a href='$f'>$f</a>" >> body
done

echo "${HEADER}
$(cat body)
${FOOTER}"