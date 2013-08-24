svn info $1 | grep ^URL | awk '{print $2}'
