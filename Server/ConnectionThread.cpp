#include "ConnectionThread.h"

ConnectionThread::ConnectionThread(int *socket, sockaddr_in srv) {
	RecvSocket = *socket;
	server = srv;
}

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
