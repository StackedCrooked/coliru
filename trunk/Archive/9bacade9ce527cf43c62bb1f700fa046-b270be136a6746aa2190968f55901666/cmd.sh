find /usr/include/c++/v1 | xargs -I {} basename {} | sort  >a
find /usr/local/include/c++/v1 | xargs -I {} basename {} | sort >b
diff -y a b