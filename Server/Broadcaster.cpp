#include "Broadcaster.h"

// Konstruktor som tar emot en vektor och lagrar den lokalt.
Broadcaster::Broadcaster(std::vector<Client*>* clientVector) {
	clients = clientVector;
	seq = 0;
}

// Returnera vektorn med klienterna.
std::vector<Client*>* Broadcaster::getClients() {
	return clients;
}

// Returnera sekvensnummret.
int Broadcaster::getSeq() {
	return seq;
}

// Plussa på seq med 1.
void Broadcaster::incrementSeq() {
	seq++;
}

// Den här metoden går igenom alla klienterna i vektorn med klienter
// och skickar meddelandet till varje klients socket.
void Broadcaster::SendMessageToAll(char* buffer, int size) {
	//std::cout << " seq in Broadcast is: " << seq;
	for (int i = 0; i < clients->size(); i++) {
		std::cout << "Sending message to ID: " << i+1 << "\n";
		send(clients->at(i)->getSocket(), buffer, size, 0);
	}
}

// Det här är en metod för att skicka till alla utom den klienten att
// klienten lämnar spelet.
void Broadcaster::SendLeave(char* buffer, int size, int clientID) {
    for (int i = 0; i < clients->size(); i++) {
        if(clients->at(i)->getClientID() != clientID) {
            std::cout << "Sending message to ID: " << i+1 << "\n";
            send(clients->at(i)->getSocket(), buffer, size, 0);
        }
	}
}
