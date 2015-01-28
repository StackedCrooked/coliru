; 在同一行中写多条命令的格式为：command1 \0 command2
; 无特殊说明的路径都是绝对路径，并且使用双引号括起来。

; 定义一些变量。
CPPFlags    = -Wall -Wextra -pedantic -Wsign-conversion -Wsuggest-attribute=noreturn -Wundef -pipe -mfpmath=both -march=nocona -masm=intel
CFlags		= -std=c11
CXXFlags	= -std=c++14 -Wzero-as-null-pointer-constant -Wnoexcept
LDFlags		= -Wall -Wextra -static -nostdlib -Wl,-e__MCF_ExeStartup,--disable-runtime-pseudo-reloc,--disable-auto-import	\
				-Wl,--wrap=atexit,--wrap=malloc,--wrap=realloc,--wrap=calloc,--wrap=free,--wrap=__cxa_throw
Libs		= -lmcflite -lstdc++ -lmingwex -lmingw32 -lgcc -lgcc_eh -lmcflite -lmsvcrt -luser32 -lkernel32

.Config {
	; 定义配置包。这些配置可以于命令行中选择。如果命令行中没有指定配置包，则使用第一个。
	Debug {
		CPPFlags	= $CPPFlags -O0 -g -fno-builtin -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC
		LDFlags		= $LDFlags -O0 -g
	}
	Release {
		CPPFlags	= $CPPFlags -O3 -ffunction-sections -fdata-sections -DNDEBUG
		LDFlags		= $LDFlags -O3 -Wl,--gc-sections,-s
	}
}

; 在构建之前执行这些命令。
.PreBuild			=
; 在构建之后执行这些命令。
.PostBuild			=

.Precompiler {
	; $.in	= 单个输入头文件路径
	; $.out	= 输出头文件路径，后缀和输入文件一样（所以对于 gcc 来说这实际是个桩文件，预编译生成的文件路径为该路径加上 .gch）

	; 名称为过滤规则（注意匹配的是全路径），斜杠（/）和反斜杠（\）交给操作系统处理。
	; 如果名称以斜杠开头并结束，则将其中的内容视为正则表达式。
	*\\StdMCF.hpp	= gcc -x c++-header $CPPFlags $CXXFlags -o $.out.gch $.in -MMD $.dep	\0\
						echo #warning Error loading precompiled header file: $.in	> $out	\0\
						echo #include $.in	>> $out
	; /regexp/		= command
}
.Compiler {
	; $.in	= 单个输入源文件路径
	; $.out	= 输出目标文件路径
	; $.pch	= 预编译输出的头文件路径

	; 指定额外的参与编译的文件，用空格隔开。
	.ExtraFiles		= ../../MCFCRT/stdc/stdlib/atexit.c ../../MCFCRT/stdc/stdlib/malloc.c ../../MCFCRT/stdc/stdlib/realloc.c	\
						../../MCFCRT/stdc/stdlib/calloc.c ../../MCFCRT/stdc/stdlib/free.c ../../MCFCRT/ext/wcscpyout.c	\
						../../MCFCRT/env/bail.c ../../MCFCRT/env/dlmalloc.c ../../MCFCRT/env/module.c ../../MCFCRT/env/last_error.c	\
						../../MCFCRT/env/fenv.c ../../MCFCRT/env/mingw_hacks.c ../../MCFCRT/env/avl_tree.c ../../MCFCRT/env/thread.c	\
						../../MCFCRT/env/heap.c ../../MCFCRT/env/heap_dbg.c ../../MCFCRT/env/cxa_throw.cpp ../../MCFCRT/exe/exe_startup.c	\
						../../MCF/Core/String.cpp ../../MCF/Core/File.cpp ../../MCF/Core/Utf8TextFile.cpp ../../MCF/Core/System.cpp	\
						../../MCF/Core/Time.cpp ../../MCF/Core/StreamBuffer.cpp ../../MCF/Thread/Thread.cpp ../../MCF/Thread/Mutex.cpp	\
						../../MCF/Thread/Semaphore.cpp ../../MCF/Languages/MNotation.cpp ../../MCF/Hash/Sha256.cpp

	; 这部分和 .Precompiler 中一样。
	*.h				= gcc -x c-header $CPPFlags $CFlags -include $.pch -fpch-deps -o $.out $.in -MMD $.dep
	*.hpp			= gcc -x c++-header $CPPFlags $CXXFlags -include $.pch -fpch-deps -o $.out $.in -MMD $.dep
}
.Linker {
	; $.in	= 所有输入目标文件路径
	; $.out	= 输出最终文件路径

	; 指定额外的参与链接的文件，用空格隔开。
	.ExtraFiles		=
	; 当命令行过长时用于合并目标文件。
	.Partial		= ld -o $.out -r $.in

	; 名称为输出文件的相对路径，值为命令行。
	MCFBuild.exe	= gcc $LDFlags -o $.out $.in $Libs
	; another.exe	= other command
}
