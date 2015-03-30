$ cat script.sh
#!/usr/bin/env bash
echo "running the script!"
lua
$ cat build.ninja
rule run-script
    command = ./$in

build run-test: run-script script.sh
build test: phony | run-test
default test
$ ninja
[1/1] ./script.sh
running the script!
$ 