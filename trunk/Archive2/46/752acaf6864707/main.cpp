#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <tr1/unordered_map>

extern "C" {

#include <errno.h>
#include <sys/mman.h>
#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdint.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct {
    uint32_t ts;
	uint32_t uid;
	uint32_t ua;
} rec;

#define cwarn(fmt, ...)   do{ \
	fprintf(stderr, "[WARN] %s:%d: ", __FILE__, __LINE__); \
	fprintf(stderr, fmt, ##__VA_ARGS__); \
	if (fmt[strlen(fmt) - 1] != 0x0a) { fprintf(stderr, "\n"); } \
	} while(0)
#define die(fmt, ...)   do{ \
	fprintf(stderr, "[WARN] %s:%d: ", __FILE__, __LINE__); \
	fprintf(stderr, fmt, ##__VA_ARGS__); \
	if (fmt[strlen(fmt) - 1] != 0x0a) { fprintf(stderr, "\n"); } \
	return(255);\
	} while(0)

}

#define AGENTS 8

typedef struct cnt {
	int hits;
	std::map <int,int> users;
	std::map <int,int> agent[AGENTS];
} cnt;



int main (int argc, char **argv) {
	int i;
	struct stat sb;
	void * addr;
	rec *r, *e;
	struct tm *tmp;
	char fmt[1024];
	
	/*
	std::map<int, cnt*> hstat;
	std::map<int, cnt*> dstat;
	cnt *ac = new cnt();
	std::map<int, cnt*>::iterator it;
	std::map<int, int>::iterator ii;
	*/
	
	std::tr1::unordered_map<int, cnt*> hstat;
	std::tr1::unordered_map<int, cnt*> dstat;
	cnt *ac = new cnt();
	std::tr1::unordered_map<int, cnt*>::iterator it;
	std::tr1::unordered_map<int, int>::iterator ii;
	
	for (i=1; i<argc; i++) {
		cwarn("%s",argv[i]);
		int fd = open(argv[i], O_RDONLY);
		if (fd == -1) die("open %s failed: %s",argv[i],strerror(errno));
		if (fstat(fd, &sb) == -1) die("fstat %s failed: %s",argv[i],strerror(errno));
		cwarn("fd = %d, size: %zd",fd, sb.st_size);
		
		addr = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE,fd, 0);
		if (addr == MAP_FAILED) die("mmap failed: %s",strerror(errno));
		r = (rec *) addr;
		e = (rec *)((char *)addr + sb.st_size);
		int count = 0;
		int cur_day = 0,cur_hour = 0;
		while (r < e) {
			time_t time = r->ts;
			int ua = r->ua > AGENTS-1 ? 0xffffffff : r->ua;
			tmp = localtime( &time );
			
			strftime(fmt,1024,"%Y%m%d",tmp);
			int day_id = atoi(fmt);
			strftime(fmt,1024,"%Y%m%d%H",tmp);
			int hour_id = atoi(fmt);
			
			cnt *hc,*dc;
			if (!( hc = hstat[hour_id] ) ) hc = hstat[hour_id] = new cnt();
			if (!( dc = dstat[day_id] ) ) dc = dstat[day_id] = new cnt();
			
			hc->hits++;
			hc->users[ r->uid ]++;
			hc->agent[ua][ r->uid ]++;
			
			dc->hits++;
			dc->users[ r->uid ]++;
			dc->agent[ua][ r->uid ]++;
			
			ac->hits++;
			ac->users[ r->uid ]++;
			ac->agent[ua][ r->uid ]++;
			
			r++;
		}
	}
	
	printf("day/hour\tnon\tios\tand\twin\tmac\tlin\twww\tunk\thits\tusers\n");
	for( it = hstat.begin(); it!= hstat.end(); ++it) {
		printf("%-16d", (*it).first);
		for (i=0; i<AGENTS; i++) {
			printf("%d\t",(*it).second->agent[i].size());
		}
		printf("%d\t",(*it).second->hits);
		printf("%d\t",(*it).second->users.size());
		printf("\n");
	}
	
	return 0;
}
