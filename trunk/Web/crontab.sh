SHELL=/bin/bash
PATH=/root/coliru/bin:/root/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games
@reboot (date > /tmp/date-check.txt)
@reboot (cd /root/coliru/Web ; nohup /root/coliru/Web/boot.sh >/dev/null 2>&1 </dev/null & disown)
