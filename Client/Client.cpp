#include "Client.h"

/**
 * Konstruktorn f�r Client.
 * @param[in] id Vad f�r id som Client objektet ska ha.
 * @param[in] position Vilken position objektet ska ha.
*/
Client::Client(int id, Coordinate position) {
	clientID = id;
	clientPosition = position;
}

/**
 * Returnera ID f�r klienten.
 * @param[out] clientID
*/
int Client::getClientID() {
	return clientID;
}

/**
 * Returnera Coordinate v�rdet klienten har.
 * @param[out] clientPosition
*/
Coordinate Client::getPosition() {
	return clientPosition;
}

/**
 * �ndra klientens Coordinate v�rde.
 * @param[in] position
*/
void Client::changeCoordinate(Coordinate position) {
	clientPosition = position;
}