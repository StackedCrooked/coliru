for i in `seq 10` ; do
    (for j in `seq 1000` ; do echo $RANDOM ; done) | sort -n | (head -n1 | xargs -I {} printf "[ {}" && tail -n1 | xargs -I {} printf "\t-\t{} ]\n")
done
