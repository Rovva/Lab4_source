#include "Broadcaster.h"

Broadcaster::Broadcaster(std::vector<Client*>* clientVector) {
	clients = clientVector;
	seq = 0;
}

std::vector<Client*>* Broadcaster::getClients() {
	return clients;
}

int Broadcaster::getSeq() {
	return seq;
}

void Broadcaster::incrementSeq() {
	seq++;
}

void Broadcaster::SendMessageToAll(char* buffer, int size) {
	//std::cout << " seq in Broadcast is: " << seq;
	for (int i = 0; i < clients->size(); i++) {
		std::cout << "Sending message to ID: " << i+1 << "\n";
		send(clients->at(i)->getSocket(), buffer, size, 0);
	}
}

void Broadcaster::SendLeave(char* buffer, int size, int clientID) {
    for (int i = 0; i < clients->size(); i++) {
        if(clients->at(i)->getClientID() != clientID) {
            std::cout << "Sending message to ID: " << i+1 << "\n";
            send(clients->at(i)->getSocket(), buffer, size, 0);
        }
	}
}
