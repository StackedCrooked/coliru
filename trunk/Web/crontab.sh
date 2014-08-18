@reboot (sleep 10 ; /root/coliru/Web/defunct-restarter.sh & disown)
@reboot (cd /root/coliru/Web ; /root/coliru/Web/logger.sh & disown)
@reboot (cd /root/coliru/Web ; /root/coliru/Web/restart.sh & disown)
