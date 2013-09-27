/*
 *
 * LLC (Linux Log Cleaner) v0.9.2
 * written by Scarab (scarab@go2.pl)
 * Created: 03.12.2001
 * Thanks goes to Mauser, MixMan, drg.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <pwd.h>
#include <utmp.h>
#include <lastlog.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define    LLCVERSION		"0.9.2"

#define UTMP_LOG	"/var/run/utmp"
#define WTMP_LOG	"/var/log/wtmp"
#define LAST_LOG	"/var/log/lastlog"

#define ON		1
#define OFF		0

#define UT_ID		3
#define MAXADDRL	16

#define UTMPSIZE	sizeof(struct utmp)
#define LASTSIZE	sizeof(struct lastlog)

#define	BMSG		"Linux Log Cleaner - written by Scarab (scarab@go2.pl)"

int usage(char *str)
{
 printf("%s\nUsage:\n", BMSG);
 printf(" %s <[-r][-R][-m]> <Options(1)> <Options(2)> <Options(3)>\n", str);
 printf("  -r - read files\n  -R - remove\n  -m - modify\n");
 printf("Options(1):\n");
 printf("  -u - path to utmp file (as default %s)\n", UTMP_LOG);
 printf("  -w - path to wtmp file (as default %s)\n", WTMP_LOG);
 printf("  -l - path to lastlog file (as default %s)\n", LAST_LOG);
 printf("Options(2):\n");
 printf(" Search:\n");
 printf("  [-N login_type], [-P pid], [-D tty], [-I term ID],\n"
	"  [-T login time], [-E username], [-H host], [-A ip address]\n");
 printf("Options(3):\n");
 printf(" Modify to:\n");
 printf("  [-n login_type], [-p pid], [-d tty], [-i term ID],\n"
	"  [-t login time], [-e username], [-h host], [-a ip address]\n");
 exit(0);
}

int err(char *err_msg)
{
 fprintf(stderr, "%s\n", err_msg);
 exit(-1);
}

int _open(char *path)
{
 int fd;

 if ((fd = open(path, O_RDWR)) < 0)
    perror("open() error");

 return fd;
}

int ll_datascheck(struct lastlog ll_tocheck, struct lastlog ll_tosearch)
{
 if (!(ll_tocheck.ll_time == ll_tosearch.ll_time || ll_tosearch.ll_time == 0))
    return OFF;
 if (!(!strncmp(ll_tosearch.ll_line, ll_tocheck.ll_line, UT_LINESIZE) || ll_tosearch.ll_line[0] == 0))
    return OFF;
 if (!(!strncmp(ll_tosearch.ll_host, ll_tocheck.ll_host, UT_HOSTSIZE) || ll_tosearch.ll_host[0] == 0))
    return OFF;

 return ON;
}

void ll_remove(int fd)
{
 if (ftruncate(fd, 0) < 0)
 {
    perror("ftruncate() error");
    fprintf(stderr, "Cannot cut file!!!\n");
 }
 else printf("OK");

 return;
}

struct lastlog ll_makestruct(struct lastlog ll_mod, struct lastlog ll_readed)
{
 if (ll_mod.ll_time != 0)
    ll_readed.ll_time = ll_mod.ll_time;
 if (ll_mod.ll_line[0] != 0)
    strncpy(ll_readed.ll_line, ll_mod.ll_line, UT_LINESIZE);
 if (ll_mod.ll_host[0] != 0)
    strncpy(ll_readed.ll_host, ll_mod.ll_host, UT_HOSTSIZE);

 return ll_readed;
}

int ut_datascheck(struct utmp ut_tocheck, struct utmp ut_tosearch)
{
 char	address1[MAXADDRL], address2[MAXADDRL];

 if (!(ut_tocheck.ut_type == ut_tosearch.ut_type || ut_tosearch.ut_type == 0))
    return OFF;
 if (!(ut_tocheck.ut_pid == ut_tosearch.ut_pid || ut_tosearch.ut_pid == 0))
    return OFF;
 if (!(ut_tocheck.ut_time == ut_tosearch.ut_time || ut_tosearch.ut_time == 0))
    return OFF;
 if (!(ut_tosearch.ut_line[0] == 0 || !strncmp(ut_tosearch.ut_line, ut_tocheck.ut_line, UT_LINESIZE)))
    return OFF;
 if (!(ut_tosearch.ut_id[0] == 0 || !strncmp(ut_tosearch.ut_id, ut_tocheck.ut_id, UT_ID)))
    return OFF;
 if (!(ut_tosearch.ut_user[0] == 0 || !strncmp(ut_tosearch.ut_user, ut_tocheck.ut_user, UT_NAMESIZE)))
    return OFF;
 if (!(ut_tosearch.ut_host[0] == 0 || !strncmp(ut_tosearch.ut_host, ut_tocheck.ut_host, UT_HOSTSIZE)))
    return OFF;
 if (ut_tosearch.ut_addr != 0)
 {
    inet_ntop(AF_INET, &ut_tosearch.ut_addr, address1, sizeof(address1));
    inet_ntop(AF_INET, &ut_tocheck.ut_addr, address2, sizeof(address2));
    if (address1[0] != 0 && strncmp(address1, address2, MAXADDRL)) return OFF;
 }

 return ON;
}

struct utmp ut_makestruct(struct utmp ut_mod, struct utmp ut_readed)
{
 if (ut_mod.ut_type != 0)
    ut_readed.ut_type = ut_mod.ut_type;
 if (ut_mod.ut_pid != 0)
    ut_readed.ut_pid = ut_mod.ut_pid;
 if (ut_mod.ut_time != 0)
    ut_readed.ut_time = ut_mod.ut_time;
 if (ut_mod.ut_addr != 0)
    ut_readed.ut_addr = ut_mod.ut_addr;
 if (ut_mod.ut_line[0] != 0)
    strncpy(ut_readed.ut_line, ut_mod.ut_line, UT_LINESIZE);
 if (ut_mod.ut_id[0] != 0)
    strncpy(ut_readed.ut_id, ut_mod.ut_id, UT_ID);
 if (ut_mod.ut_user[0] != 0)
    strncpy(ut_readed.ut_user, ut_mod.ut_user, UT_NAMESIZE);
 if (ut_mod.ut_host[0] != 0)
    strncpy(ut_readed.ut_host, ut_mod.ut_host, UT_HOSTSIZE);

 return ut_readed;
}

void ut_remove(int fd, struct utmp s_utmp, size_t f_size)
{
 short          cw = OFF;
 int            n = 0;
 size_t         cut_file, wr_ptr = 0, pos_ptr = 0;
 struct utmp    tmp;

 lseek(fd, 0, SEEK_SET);
 memset(&tmp, 0, UTMPSIZE);

 while(read(fd, &tmp, UTMPSIZE) > 0)
 {
    pos_ptr += UTMPSIZE;

    if (ut_datascheck(tmp, s_utmp) == ON)
    {
       if (wr_ptr == 0) wr_ptr = pos_ptr - UTMPSIZE;

       n++;
       cw = ON;
    }
    else
    {
       if (cw == ON)
       {
          lseek(fd, wr_ptr, SEEK_SET);
          write(fd, &tmp, UTMPSIZE);
          lseek(fd, pos_ptr, SEEK_SET);
          wr_ptr += UTMPSIZE;
       }
    }

    memset(&tmp, 0, UTMPSIZE);
 }

 cut_file = f_size - (n * UTMPSIZE);

 if (ftruncate(fd, cut_file) < 0)
 {
    perror("ftruncate() error");
    printf("Cannot cut file\n");
 }
 else
    if (n == 0) printf("Not changed");
    else printf("OK");
}

int main(int argc, char **argv)
{
 short		modifyopt = OFF, removeopt = OFF, readopt = OFF;
 int		ofile = 0, n;
 int		filedestab[3];
 double		total = 0, num = 0;
 size_t		filesize;
 char		ch;
 char		*utmp_f = UTMP_LOG, *wtmp_f = WTMP_LOG, *last_f = LAST_LOG;
 char		*filestab[2];
 char		buff[MAXADDRL];
 struct	utmp	ut_setto, ut_search, ut_read, ut_write;
 struct lastlog	ll_setto, ll_search, ll_read, ll_write;

 opterr = 0;

 memset(&ut_setto, 0, UTMPSIZE);
 memset(&ll_setto, 0, LASTSIZE);
 memset(&ut_search, 0, UTMPSIZE);
 memset(&ll_search, 0, LASTSIZE);

 if (argc == 1)
    usage(*argv);

 while((ch = getopt(argc, argv, "N:n:P:p:T:t:H:h:I:i:D:d:E:e:S:s:A:a:u:w:l:mRrv")) != EOF)
 {
    switch(ch)
    {
       case 'm':
	    modifyopt = ON; break;
       case 'R':
	    removeopt = ON; break;
       case 'r':
	    readopt = ON; break;
       case 'u':
	    utmp_f = optarg; break;
       case 'w':
            wtmp_f = optarg; break;
       case 'l':
	    last_f = optarg; break;
       case 'N':
	    ut_search.ut_type = atoi(optarg); break;
       case 'n':
	    ut_setto.ut_type = atoi(optarg); break;
       case 'P':
	    ut_search.ut_pid = atoi(optarg); break;
       case 'p':
	    ut_setto.ut_pid = atoi(optarg); break;
       case 'D':
	    strncpy(ut_search.ut_line, optarg, UT_LINESIZE);
	    strncpy(ll_search.ll_line, optarg, UT_LINESIZE);
	    break;
       case 'd':
	    strncpy(ut_setto.ut_line, optarg, UT_LINESIZE);
	    strncpy(ll_setto.ll_line, optarg, UT_LINESIZE);
	    break;
       case 'I':
	    strncpy(ut_search.ut_id, optarg, UT_ID); break;
       case 'i':
	    strncpy(ut_setto.ut_id, optarg, UT_ID); break;
       case 'T':
            ut_search.ut_time = atol(optarg);
            ll_search.ll_time = atol(optarg);
            break;
       case 't':
	    ut_setto.ut_time = atol(optarg);
	    ll_setto.ll_time = atol(optarg);
	    break;
       case 'E':
            strncpy(ut_search.ut_user, optarg, UT_NAMESIZE); break;
       case 'e':
	    strncpy(ut_setto.ut_user, optarg, UT_NAMESIZE); break;
       case 'H':
            strncpy(ut_search.ut_host, optarg, UT_HOSTSIZE);
            strncpy(ll_search.ll_host, optarg, UT_HOSTSIZE);
            break;
       case 'h':
	    strncpy(ut_setto.ut_host, optarg, UT_HOSTSIZE);
	    strncpy(ll_setto.ll_host, optarg, UT_HOSTSIZE);
	    break;
       case 'A':
            if (inet_pton(AF_INET, optarg, &ut_search.ut_addr) < 1) 
	    {
	       fprintf(stderr, "inet_pton error for %s\n", optarg);
               exit(-3);
            }
            break;
       case 'a':
            if (inet_pton(AF_INET, optarg, &ut_setto.ut_addr) < 1)
	    {
     	       fprintf(stderr, "inet_pton error for %s\n", optarg);
               exit(-4);
            }
            break;
       case 'v':
	    printf("LLC v%s\n", LLCVERSION); exit(0);	
       default:
            usage(*argv);
    }
 }

 if (modifyopt == OFF && removeopt == OFF && readopt == OFF)
    err("You must specify what do you want to do (e.g. <-m>, <-R> or <-r>)");

 filestab[0] = utmp_f;
 filestab[1] = wtmp_f;
 filestab[2] = last_f;

 for(n = 0 ; n < 3 ; ++n)
 {
    if ((filedestab[n] = _open(filestab[n])) != -1) ofile++;
    else fprintf(stderr, "Cannot open %s\n", filestab[n]);
 }

 if (ofile == 0)
    err("Opened files not found");

 if (!(removeopt == ON || modifyopt == ON || readopt == ON))
    err("Cannot use <-m>, <-R> or <-r> together");

 memset(&ut_read, 0, UTMPSIZE);
 memset(&ll_read, 0, LASTSIZE);
 memset(&ut_write, 0, UTMPSIZE);
 memset(&ll_write, 0, LASTSIZE);

 printf("%s\n", BMSG);

 if (readopt == ON)
 {
    for(n = 0 ; n < 3; ++n)
    {
       printf("\nProcessing %s: ", filestab[n]);
       if (filedestab[n] != -1)
       {
	  putchar('\n');
	  if (n < 2)
	  {
	     while(read(filedestab[n], &ut_read, UTMPSIZE) > 0)
	     {     
		if (ut_datascheck(ut_read, ut_search) == ON)
		{
		   inet_ntop(AF_INET, &ut_read.ut_addr, buff, sizeof(buff));
		   printf("dev: %s, user: %s, host: %s, ip: %s, pid: %d, type: %d, time: %ld,"
	 		  "id: %s\n", ut_read.ut_line, ut_read.ut_user, ut_read.ut_host, buff,
                           ut_read.ut_pid, ut_read.ut_type, ut_read.ut_time, ut_read.ut_id);
                }

	     }
	  }
	  else
          {
              if (read(filedestab[n], &ll_read, LASTSIZE) > 0)
              {
                 if (ll_datascheck(ll_read, ll_search) == ON)
       		    printf("dev: %s, host: %s, time: %ld\n", ll_read.ll_line, ll_read.ll_host, ll_read.ll_time);
			
	      }
	  }
       }
       else printf("file ignored!!!\n");
    }
 }

 if (modifyopt == ON)
 {
    for(n = 0 ; n < 3; n++)
    {
       printf("\nProcessing %s: ", filestab[n]);
       if (filedestab[n] != -1)
       {
          if (n < 2)
          {
             while(read(filedestab[n], &ut_read, UTMPSIZE) > 0)
             {
		total++;
                if (ut_datascheck(ut_read, ut_search) == ON)
                {
                   memset(&ut_write, 0, UTMPSIZE);
                   ut_write = ut_makestruct(ut_setto, ut_read);
                   lseek(filedestab[n], -UTMPSIZE, SEEK_CUR);
                   write(filedestab[n], &ut_write, UTMPSIZE);
                   num++;
                }
             }

	     filesize = lseek(filedestab[n], 0, SEEK_END);
             if (filesize == 0) printf("File is empty");
	     else printf("total: %.0f, changed: %.0f", total, num);
          }
          else
          {
             if (read(filedestab[n], &ll_read, LASTSIZE) > 0)
             {
	        if (ll_datascheck(ll_read, ll_search) == ON)
	        {
                   ll_write = ll_makestruct(ll_setto, ll_read);
	           lseek(filedestab[n], -LASTSIZE, SEEK_CUR);
                   write(filedestab[n], &ll_write, LASTSIZE);
                   printf("OK");
	        }
		else printf("Not changed");
             }
	     else
	     {
	        filesize = lseek(filedestab[n], 0, SEEK_END);
	        if (filesize == 0) printf("File is empty");
	     }
          }
       }
       else printf("file ignored!!!\n");
    }
 }

 if (removeopt == ON)
 {
    for(n = 0 ; n < 3; ++n)
    {
       printf("\nProcessing %s: ", filestab[n]);
       if (filedestab[n] != -1)
       {
          if (n < 2)
	  {
	     filesize = lseek(filedestab[n], 0, SEEK_END);
             if (filesize == 0) printf("File is empty");
	     else ut_remove(filedestab[n], ut_search, filesize);
	  }
          else
          {
             if (read(filedestab[n], &ll_read, LASTSIZE) > 0)
             {
	        if (ll_datascheck(ll_read, ll_search) == ON)
	           ll_remove(filedestab[n]);
	        else printf("Not changed");
             }
	     else
	     {
	        filesize = lseek(filedestab[n], 0, SEEK_END);
 	        if (filesize == 0) printf("File is empty\n");
             }
	  }
       }
       else printf("file ignored!!!\n");
    }
 }

 printf("\n\nDone...\n");
 return 0;
}
