download() {
  echo "Downloading $FILE..." && \
  wget -q ${URL} --output-document="${FILE}.part" && \
  mv "${FILE}.part" ${FILE}
  WAIT=$((5 + $RANDOM % 10))
  echo "Wait for ${WAIT} seconds until next download."
  sleep ${WAIT}
}

while read URL ; do
  FILE=`echo ${URL} | cut -d "=" -f 4 | sed "s,\$,.mkv,"`
  if [ -f ${FILE} ] ; then echo "${FILE} already downloaded."
  elif [ -f "${FILE}.part" ] ; then rm "${FILE}.part" && download
  else download
  fi
done < $1
