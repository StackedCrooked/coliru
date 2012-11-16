ssh -p 2222 localhost 'cd /home/francis/programming/projects/stacked-crooked/Playground/OverrideMalloc && LD_PRELOAD=./libmalloc_hook.so ./test'
