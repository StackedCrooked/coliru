canary.
iPhone:~ root# uname -a
Darwin iPhone 14.0.0 Darwin Kernel Version 14.0.0: Fri Mar 28 21:15:11 PDT 2014; root:xnu-2423.10.70~1/RELEASE_ARM_S5L8950X iPhone5,2 arm N42AP Darwin
iPhone:~ root# sysctl kern.osversion
kern.osversion: 11D201
iPhonestack_guard=0x55446677
iPhone:~ root# ln -sf ../appledump stack_guard\=0x55446677/link
iPhone:~ root# stack_guard\=0x55446677/link
string(0):
string(1):
string(2): stack_guard=0x0b004be3aceda6a7
string(3):
__stack_chk_guard: 0000000055446677
And the corresponding appledump.c is the following code:
extern long __stack_chk_guard[8];
int main(int argc, char **argv, char **envp, char **apple)
{
int i;
for (i=0; apple[i]; i++) {
printf("string(%u): %s\n", i, apple[i]);
}
printf("\n\n__stack_chk_guard: %016lx\n", *(long *)__stack_chk_guard);
}
At the time of writing it is still unknown why Apple hasn't fixed their exploit mitigation for.
Stefan Esser