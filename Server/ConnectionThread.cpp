#include "ConnectionThread.h"

// Konstruktorn tar emot en socket och sockaddr som är nödvändigt för att 
// etablera och upprätthålla anslutningar till klienter.
ConnectionThread::ConnectionThread(int *socket, sockaddr_in srv) {
	RecvSocket = *socket;
	server = srv;
}

// Det här är metoden som ska köras om och om igen i en tråd.
// Dess uppgift är att ta emot anslutningar från klienter.
void ConnectionThread::operator()(Broadcaster *broad, int *seq) {
	int tmpSocket;
	socklen_t addrSize = sizeof(server);

	while (1) {
		// När en anslutning är mottagen så skapar tråden ett ReaderThread objekt
		// i en ny tråd som hanterar den specifika anslutningen och input/output.
		if (tmpSocket = accept(RecvSocket, (struct sockaddr*)&server, &addrSize)) {
			std::thread clientThread(ReaderThread(tmpSocket), broad);
			clientThread.detach();
		}
	}
}
