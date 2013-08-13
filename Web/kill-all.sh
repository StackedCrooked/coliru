ps -eopgid,ppid,pid,comm | grep 'restart.sh' | awk '{print $1}'
