while read COMMAND ; do
  echo "Command: ${COMMAND}"
  export ERROR="0"
  { printf "Output: " ; ${COMMAND} 2>&1 ; printf "Exit code: $?" ; } | perl -pe 's,\n,\\n,g' >OUTPUT
  cat OUTPUT | perl -pe 's,Exit code,\nExit code,g'
  echo
done