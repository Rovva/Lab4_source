#include "Client.h"

Client::Client(int id, int socket) {
	clientID = id;
	clientSocket = socket;
}

int Client::getClientID() {
	return clientID;
}

void Client::setPosition(Coordinate newPosition) {
	position = newPosition;
}

Coordinate Client::getPosition() {
	return position;
}

int Client::getSocket() {
	return clientSocket;
}
