#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

int main (int argc, char **argv) {
	if (argc < 3) {
		cout << "Incorrect number of arguments.\n";
		exit(1);
	}

	if (argc > 3) {
		cout << "Incorrect number of arguments\n";
		exit(1);
	}

	int cliSocket;
	struct sockaddr_in servAddr;
	struct sockaddr_in cliAddr;
	unsigned int cliLen;
	char buffer[150];
	char *storedMessage = (char*) malloc(151);

	char *ip_addr = argv[1];
	unsigned short servPort = atoi(argv[2]);
	int servSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(ip_addr);
	servAddr.sin_port = htons(servPort);

	bind(servSocket, (struct sockaddr *) &servAddr, sizeof(servAddr));
	listen(servSocket, 5);

	int flag = 0;
	while (flag == 0) {
		cliLen = sizeof(cliAddr);
		cliSocket = accept(servSocket, (struct sockaddr *) &cliAddr, &cliLen);
		recv(cliSocket, buffer, 149, 0);
		char mode = buffer[1];
		if (mode == 'd') {
			cout << "here" << endl;
			send(cliSocket, storedMessage, strlen(storedMessage), 0);
		}
		if (mode == 'u') {
			int count = 0;
			for (int i = 0; i < strlen(buffer); i++) {
				if (i != 0 && i != 1) {
					storedMessage[count] = buffer[i];
					count++;
				}
			}
			memset(&buffer, 0, sizeof(buffer));
			cout << "Current stored message: " << storedMessage << endl;
		}
	}
}