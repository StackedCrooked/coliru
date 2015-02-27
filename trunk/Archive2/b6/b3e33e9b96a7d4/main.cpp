	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#ifdef WIN32
  #include <winsock2.h>
#else
  #define SOCKET_ERROR 0
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <netdb.h>
#endif
 
 
 
#define PROGRAM_NAME "Send Mayl 1.0 Beta"
#define PORT 25
#define MAX_CHAR_LENGTH 60
#define MAX_MESSAGE_LENGTH 4096
 
//Funzione per chiudere il socket, visto che Microsoft deve avere sempre tutto diverso...
#ifdef WIN32
void close(int sock){
  closesocket(sock);
  return;
}
#endif
 
 
 
int init_smtp_sock(char *target);
int send_packet(int sock, char *message);
char *recv_packet(int sock);
int check_ok(char *string);
char *read_input(int maxlength, char *x_char);
int remove_n(char *string);
char *convert_to_mime(char *string, int change_spaces);
 
int main(int argc, char *argv[]){
 //Dichiara le variabili...
 int sock;
 char *target;
 char *mail_from;
 char *mail_to;
 char *subject;
 char *message;
 char *buffer;
 
 //Imposta l'helo...
 char *helo;
 helo=malloc(sizeof(char)*MAX_CHAR_LENGTH);
 strcpy(helo,"helo ");
 strcat(helo,PROGRAM_NAME);
 strcat(helo,"\n\0");
 
 
 //Alloca la memoria...
 target=malloc(sizeof(char)*MAX_CHAR_LENGTH);
 mail_from=malloc(sizeof(char)*MAX_CHAR_LENGTH);
 mail_to=malloc(sizeof(char)*MAX_CHAR_LENGTH);
 subject=malloc(sizeof(char)*MAX_CHAR_LENGTH);
 buffer=malloc(sizeof(char)*MAX_CHAR_LENGTH);
 
 
 printf("%s is starting up...\n\n",PROGRAM_NAME);
 
 printf("SMTP server address (mail.libero.it): ");
 scanf("%s",target);
 
 //Connetti...
 sock=init_smtp_sock(target);
 
 //Libera la memoria di target...
 free(target);
 
 //Riceve il messaggio di benvenuto...
 recv_packet(sock);
 
 //Invia il comando helo...
 send_packet(sock,helo);
 
 //Riceve la risposta ad helo...
 recv_packet(sock);
 
 //Chiede all'utente l'indirizzo del mittente e continua il ciclo finche il server non da l'OK
 do{
 
 printf("Mail From (foo@linux.org): ");
 scanf("%s",mail_from);
 sprintf(buffer,"MAIL FROM:<%s>\n\0",mail_from);
 
 //Invia l'indirizzo del mittente...
 send_packet(sock,buffer);
 
 }while(!check_ok(recv_packet(sock)));
 
 
 //Stesso procedimento per l'indirizzo del destinatario...
 do{
 
 printf("Mail To (victim@linux.org): ");
 scanf("%s",mail_to);
 sprintf(buffer,"RCPT TO:<%s>\n\0",mail_to);
 
 //Invia l'indirizzo del destinatario...
 send_packet(sock,buffer);
 
 }while(!check_ok(recv_packet(sock)));
 
//Invia il comando DATA per iniziare a scrivere l'email...
 send_packet(sock,"DATA\n\0");
 
 //Riceve la conferma con le specifiche per terminare il messaggio...
 recv_packet(sock);
 
 //Invia il comando Message-ID:
 send_packet(sock,"Message-ID:\n\0");
 
 //Invia nuovamente l'indirizzo del mittente... (MIME)
 sprintf(buffer,"FROM:<%s>\n\0",mail_from);
 send_packet(sock,buffer);
 
 //Invia nuovamente l'indirizzo del destinatario... (MIME)
 sprintf(buffer,"TO:<%s>\n\0",mail_to);
 send_packet(sock,buffer);
 
 //Libera la memoria di mail_from, mail_to
 free(mail_from);
 free(mail_to);
 
  //Chiede all'utente un Subject...
 printf("Subject: ");
 
 //(non chiedetemi perchè ho messo 2 volte il comando fgets, ma senza metterlo 2 volte non funziona correttamente...)
 fgets(subject,MAX_CHAR_LENGTH,stdin);
 fgets(subject,MAX_CHAR_LENGTH,stdin);
 remove_n(subject);
 
 //Se è ambiente diverso da windows si può modificare il Subject rendendolo compatibile con lo standard MIME...
 #ifdef WIN32
  //Invia il Subject senza il MIME (windows)
  sprintf(buffer,"Subject: %s\n\0",subject);
  send_packet(sock,buffer);
 #else
  subject=convert_to_mime(subject,1);
  //Invia il Subject con il MIME (linux/unix)
  sprintf(buffer,"Subject: =?iso-8859-1?Q?%s?=\n\0",subject);
  send_packet(sock,buffer);
 #endif
 
 //Chidede l'input per il testo dell'email...
 printf("Message: ");
 message=read_input(MAX_MESSAGE_LENGTH,"\n\n");
 
 //Se è ambiente diverso da windows si può modificare il messaggio rendendolo compatibile con lo standard MIME...
 #ifdef WIN32
  //Invia il messaggio...
  sprintf(buffer,"\n%s\n\0",message);
  send_packet(sock,buffer);
 #else
  //Modifica il messaggio rendendolo compatibile con lo standard MIME...
  message=convert_to_mime(message,0);
  //Invia le informazioni per la codifica...
  send_packet(sock,"Content-Type: text/plain;charset=\"iso-8859-1\"\n\0");
  send_packet(sock,"Content-Transfer-Encoding: quoted-printable\n\0");
  //Invia il messaggio...
  sprintf(buffer,"\n%s\n\0",message);
  send_packet(sock,buffer);
 #endif
 
 //Invia la conferma per l'invio...
 printf("Sending message... ");
 send_packet(sock,".\n\0");
 check_ok(recv_packet(sock)) ? printf("OK\n") : printf("Failed\n");
 
 //Chiude la connessione...
 printf("Closing connection... ");
 send_packet(sock,"QUIT\n\0");
 close(sock);
 printf("OK\n");
 
 
 //Chiude il programma correttamente...
  exit(EXIT_SUCCESS);
}
 
 
 
int remove_n(char *string){
 int len=strlen(string);
 int count;
 
 for(count=0;count<len;count++){
  if (string[count]=='\n') string[count]='\0';
 }
 return 1;
}
 
 
//Ma quanto odio il MIME... tuttavia questa funzione risolve le cose (solo in ambiente linux/unix)
 
char *convert_to_mime(char *string, int change_spaces){
 char *buffer;
 unsigned char ch;
 unsigned int count,pointer;
 
 
 buffer=malloc(sizeof(char)*(strlen(string)*3)+1);
 
 for (count=pointer=0; count<strlen(string); pointer++){
  ch=string[count++];
 
  //Se è un carattere esteso...
  if (ch & 0x80){
   sprintf(buffer+pointer,"=%X",ch);
   pointer+=2;
  }else{
   buffer[pointer]=((change_spaces && ch==' ') ? '_' : ch);
  }
 }
 
 buffer[pointer]='\0';
 return buffer;
 
}
 
 
 
 
 
char *read_input(int maxlength, char *x_char){
 char *buffer;
 char ch;
 int count=0;
 
 buffer=malloc(sizeof(char)*maxlength);
 
 do{
  ch=getchar();
  buffer[count]=ch;
  count++;
 }while(!strstr(buffer,x_char));
 buffer[count]='\0';
 return buffer;
}
 
int check_ok(char *string){
 if(strstr(string,"OK") || strstr(string,"ok") || strstr(string,"250")){
  return 1;
 }else{
  printf("%s\n",string);
  return 0;
 }
}
 
 
int send_packet(int sock, char *message){
 int len=strlen(message);
 
 send(sock,message,len,0);
 return 1;
}
 
 
 
char *recv_packet(int sock){
 char *buffer;
 int res;
 
 buffer=malloc(sizeof(char)*MAX_CHAR_LENGTH);
 
 res=recv(sock,buffer,MAX_CHAR_LENGTH,0);
 
 //Se ha finito, chiude la stringa con il carattere di chiusura.
 if (res>=0){
  *(buffer+res)='\0';
 }
 return buffer;
}
 
 
 
 
int init_smtp_sock(char *target){
 struct sockaddr_in client;
 struct hostent *hostinfo;
 int sock;
 
 //Se l'ambiente è windows bisogna inizializzare il socket...
#ifdef WIN32
 WORD version;
 WSADATA WSAData;
 version=MAKEWORD(1,1);
 WSAStartup(version, &WSAData);
#endif
 
 //Avvia il socket
 printf("Initialyzing the socket... ");
 if ((sock=socket(AF_INET,SOCK_STREAM,0))==SOCKET_ERROR){
  printf("Failed\n");
  exit(EXIT_FAILURE);
 }
 printf("OK\n");
 
 //Risolve il DNS
 printf("Resolving DNS... ");
 hostinfo=gethostbyname(target);
 if (hostinfo==NULL){
  printf("Failed\n");
  exit(EXIT_FAILURE);
 }
 printf("OK\n");
 
 //Imposta la connessione con il server...
 client.sin_family=AF_INET;
 client.sin_addr=*((struct in_addr *)hostinfo->h_addr);
 client.sin_port=htons(PORT);
 
 
 //Si connette al server...
 printf("Connecting to %s... ",target);
 if (connect(sock,(struct sockaddr *)&client, sizeof(client))){
  printf("Failed\n");
  exit(EXIT_FAILURE);
 }
 printf("OK\n\n");
 
 return sock;
}