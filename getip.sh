netstat -n -t | awk '{print $4}' | grep -o "[0-9]*\.[0-9]*\.[0-9]*\.[0-9]*" | grep -v "127.0.0.1"
