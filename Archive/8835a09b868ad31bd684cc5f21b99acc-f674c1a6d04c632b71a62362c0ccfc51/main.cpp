#pragma once

#ifdef PLATFORM_WINDOWS
    #define BREAKPOINT _CrtDbgBreak();
#else
	#ifdef PLATFORM_LINUX
		#define BREAKPOINT asm volatile ("int3;");
	#else
		#error "No platform defined"
	#endif
#endif