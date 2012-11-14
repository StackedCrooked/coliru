VBoxManage modifyvm "ubuntu-10.04.4-server-amd64" --natpf1 "guesthttp,tcp,,8080,,80"
VBoxManage modifyvm "ubuntu-10.04.4-server-amd64" --natpf1 "guesthttp,tcp,,2222,,22"
