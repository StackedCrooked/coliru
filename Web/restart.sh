exec > >(logger -t $0) 2>&1
{ ./kill-all.sh && ./run.sh ; } & disown
