set -x
sudo -u sandboxer bin/process-request-sandboxed.sh &
echo "Timeout after 2 second."
sleep 2
echo "Time's up!"
ps -ef | grep "bin/process-request-sandboxed.sh" | awk '{print $3}' | xargs -I PID kill -9 PID
echo "Timed out!"
