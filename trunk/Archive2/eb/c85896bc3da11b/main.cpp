#if 0
stacked-crooked ~/tmp/5ae856e591bbf7 # strace ghc --make main 2>&1 | grep '"\/' | perl -pe 's,.*?"(\/.*)".*,\1,g' | sort -u
+ grep --color=auto '"\/'
+ perl -pe 's,.*?"(\/.*)".*,\1,g'
+ sort -u
+ strace ghc --make main
/etc/ld.so.cache
/etc/ld.so.nohwcap
/etc/ld.so.preload
/lib/x86_64-linux-gnu/libc.so.6
/lib/x86_64-linux-gnu/libdl.so.2
/lib/x86_64-linux-gnu/libm.so.6
/lib/x86_64-linux-gnu/libpthread.so.0
/lib/x86_64-linux-gnu/librt.so.1
/lib/x86_64-linux-gnu/libtinfo.so.5
/root/.cabal/lib/mtl-2.1.2/ghc-7.4.1/Control/Monad/State.hi
/root/.cabal/lib/mtl-2.1.2/ghc-7.4.1/libHSmtl-2.1.2.a
/root/.cabal/lib/transformers-0.3.0.0/ghc-7.4.1/libHStransformers-0.3.0.0.a
/root/.ghc/x86_64-linux-7.4.1/package.conf.d
/root/.ghc/x86_64-linux-7.4.1/package.conf.d/package.cache
/root/tmp/5ae856e591bbf7
/tmp/ghc22520_0
/tmp/ghc22520_0/ghc22520_0.s
/usr/bin/ghc
/usr/bin/ghc", ["ghc", "--make", "main
/usr/lib/ghc/base-4.5.0.0/libHSbase-4.5.0.0.a
/usr/lib/ghc/base-4.5.0.0/Prelude.hi
/usr/lib/ghc/base-4.5.0.0/System/IO.hi
/usr/lib/ghc/ghc-prim-0.2.0.0/libHSghc-prim-0.2.0.0.a
/usr/lib/ghc/integer-gmp-0.4.0.0/libHSinteger-gmp-0.4.0.0.a
/usr/lib/ghc/l
/usr/lib/ghc/lib/ghc", ["/usr/lib/ghc/lib/ghc", "-B/usr/lib/ghc", "--make", "main
/usr/lib/ghc/package.conf.d
/usr/lib/ghc/package.conf.d/package.cache
/usr/lib/ghc/settings
/usr/lib/locale/locale-archive
/usr/lib/x86_64-linux-gnu/libffi.so.6
/usr/lib/x86_64-linux-gnu/libgmp.so.10
++ [[ 0 != 0 ]]
#endif