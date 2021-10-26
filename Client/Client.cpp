#include "Client.h"

/**
 * Konstruktorn för Client.
 * @param[in] id Vad för id som Client objektet ska ha.
 * @param[in] position Vilken position objektet ska ha.
*/
Client::Client(int id, Coordinate position) {
	clientID = id;
	clientPosition = position;
}

/**
 * Returnera ID för klienten.
 * @param[out] clientID
*/
int Client::getClientID() {
	return clientID;
}

/**
 * Returnera Coordinate värdet klienten har.
 * @param[out] clientPosition
*/
Coordinate Client::getPosition() {
	return clientPosition;
}

/**
 * Ändra klientens Coordinate värde.
 * @param[in] position
*/
void Client::changeCoordinate(Coordinate position) {
	clientPosition = position;
}