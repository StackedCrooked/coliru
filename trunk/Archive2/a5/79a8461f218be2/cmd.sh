echo "<html>
<body>
$(while read line ; do
  i=$(($i + 1))
  echo "<a href=\"$line\">$i</a>"
done <main.cpp)
</body>
</html>
"