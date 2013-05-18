exec > >(logger -t $0) 2>&1
{ ./kill-current.sh  && ./run.sh ; } & disown
