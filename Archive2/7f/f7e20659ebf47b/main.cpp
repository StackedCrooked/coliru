#include <iostream>
#include <ctype.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

int sock;
struct sockaddr_in client;
int PORT = 80;

void setupSocket(char* hostname) {
    struct hostent * host = gethostbyname(hostname);

	if ( (host == NULL) || (host->h_addr == NULL) ) {
		cout << "Error retrieving DNS information." << endl;
		exit(1);
	}

	bzero(&client, sizeof(client));
	client.sin_family = AF_INET;
	client.sin_port = htons( PORT );
	memcpy(&client.sin_addr, host->h_addr, host->h_length);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sock < 0) {
		cout << "Error creating socket." << endl;
		exit(1);
	}
}

void connectToHost(char* hostname) {
	if ( connect(sock, (struct sockaddr *)&client, sizeof(client)) < 0 ) {
		close(sock);
		cout << "Could not connect to " << hostname << endl;
		exit(1);
	}
}

void sendRequest(char* hostname) {
	string request = "GET / HTTP/1.1\r\nHost: ";
	request+= string(hostname);
	request += "\r\n\r\n";
	
	if (send(sock, request.c_str(), request.length(), 0) != (int)request.length()) {
		cout << "Error sending request." << endl;
		exit(1);
	}
}

void getResponse() {
	char cur;
	while ( read(sock, &cur, 1) > 0 ) {
		cout << cur;
	}
}

int main(int argc, char** argv) {
	setupSocket(argv[1]);
	connectToHost(argv[1]);
	sendRequest(argv[1]);
	getResponse();
	
	return 0;
}
