VBoxManage modifyvm "coliru" --natpf1 delete guestssh
VBoxManage modifyvm "coliru" --natpf1 "guestssh,tcp,,2222,,22"

VBoxManage modifyvm "coliru" --natpf1 delete guesthttp
VBoxManage modifyvm "coliru" --natpf1 "guesthttp,tcp,,8080,,80"
