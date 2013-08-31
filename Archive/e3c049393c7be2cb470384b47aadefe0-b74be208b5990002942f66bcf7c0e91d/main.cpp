set +x

printf "\n\n--- /Archive/wide ---\n"
find /Archive/wide/ClangExperiments -name '*.o'


printf "\n\n--- Current Link Command ---\n"
cat /Archive/wide/link.sh | perl -p -e 's, \., \\\n  \.,g'


printf "\n\n--- /Archive/LLVM/Clang/build/Release ---\n"
find  /Archive/LLVM/Clang/build/Release -name '*.a' -or -name '*.so'
