#include "SocketSetup.h"

SocketSetup::SocketSetup() {

    RecvSocket = socket(AF_INET, SOCK_STREAM, 0);

	// Nulla minnet i området där server lagras eftersom det kan finnas gammal data där.
    memset(&server, '0', sizeof(server));
	
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(49152);

    bind(RecvSocket, (struct sockaddr*)&server, sizeof(server));

	// Lyssna efter inkommande anslutningar.
    listen(RecvSocket, 3);

    puts("Waiting for incoming connections...");

}

int SocketSetup::getSocket() {
    return RecvSocket;
}

sockaddr_in SocketSetup::getServer() {
    return server;
}
