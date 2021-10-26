#include <iostream>
#include <vector>
#include <thread>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "SocketSetup.h"
#include "ConnectionThread.h"
#include "Client.h"
#include "ReaderThread.h"
#include "Broadcaster.h"
#ifndef MESSAGES_H
#define MESSAGES_H
#include "Messages.h"
#endif

int main()
{
    int test = 0;

	// Skapa en vektor som lagrar alla klienterna.
    std::vector<Client*>* clients = new std::vector<Client*>;

	// Seq anv�nds f�r att ber�kna sekvensnummret som skickas i meddelanden.
    int seq = 0;

	// Skapa SocketSetup objekt f�r att uppr�tta en socket som klienter ansluter till.
    SocketSetup* socket = new SocketSetup();

	// Lagra den tidigare skapade socketen.
    int RecvSocket = socket->getSocket();
	// Lagra serveradressen.
    sockaddr_in server = socket->getServer();

	// Skapa Broadcaster objekt som skickar meddelanden till alla klienterna.
    Broadcaster* broad = new Broadcaster(clients);

	// Skapa ConnectionThread objektet och k�r den i en tr�d.
    std::thread connection(ConnectionThread(&RecvSocket, server), broad, &seq);
    connection.detach();
	// Loopa i o�ndligheten.
    while (1) {

    }
}
