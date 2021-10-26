#include "Client.h"

// Konstruktor för en klient som tar emot id och socket. id är clientens id
// och socket är den nyligen skapade socket från ConnectionThread.
Client::Client(int id, int socket) {
	clientID = id;
	clientSocket = socket;
}

// Returnera klientens id.
int Client::getClientID() {
	return clientID;
}

// Ändrar position på klienten.
void Client::setPosition(Coordinate newPosition) {
	position = newPosition;
}

// Returns the clients position in a Coordinate type variable.
// Returnerar klientens position iform av "Coordinate" typ.
Coordinate Client::getPosition() {
	return position;
}

// Returnerar den lagrade socketen för klienten.
int Client::getSocket() {
	return clientSocket;
}
