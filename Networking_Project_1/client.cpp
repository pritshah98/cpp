#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

void download (int sock, char *mode) {
	char buffer[150];
	send(sock, mode, strlen(mode), 0);
	recv(sock, buffer, 149, 0);
	cout << "HERE" << endl;
	if (strlen(buffer) == 0) {
		cout << "Empty message." << endl;
	} else {
		cout << buffer << endl;
		cout << "Server message downloaded." << endl;
	}
}

void upload (int sock,	char *mode,	char *message, unsigned int messageLen) {
	char *srvMessage = strcat(mode, message);
	send(sock, srvMessage, strlen(srvMessage), 0);
}

int main (int argc, char **argv) {
	if (argc < 4) {
		cout << "Incorrect number of arguments.\n";
		exit(1);
	}

	if (argc > 5) {
		cout << "Incorrect number of arguments\n";
		exit(1);
	}

	char *mode = argv[3];
	char *message;
	unsigned int messageLen;
	if (argc == 5) {
		message = argv[4];
		messageLen = strlen(message);
		if (strlen(message) > 150) {
			cout << "Message is too many characters." << endl;
			exit(1);
		}
	}

	struct sockaddr_in servAddr;
	char *ip_addr = argv[1];
	unsigned short servPort = atoi(argv[2]);

	int cliSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(ip_addr);
	servAddr.sin_port = htons(servPort);

	connect(cliSock, (struct sockaddr *) &servAddr, sizeof(servAddr));

	if (strncmp(mode, "-d", 2) == 0) {
		download(cliSock, mode);
	}

	if (strncmp(mode, "-u", 2) == 0) {
		upload(cliSock, mode, message, messageLen);
	}

	close(cliSock);
	exit(0);
}