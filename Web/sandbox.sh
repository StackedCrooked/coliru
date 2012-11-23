ulimit -t 1
ulimit -n 20
cp main.cpp /var/chroot/home/lol/main.cpp
echo "cd /home/lol && bash main.cpp" >/var/chroot/home/lol/build.sh
chroot /var/chroot bash /home/lol/build.sh
