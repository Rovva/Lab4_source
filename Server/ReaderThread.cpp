#include "ReaderThread.h"

// Konstruktor som tar en socket som parameter och lagrar den lokalt.
ReaderThread::ReaderThread(int socket) {
	RecvSocket = socket;
	clientID = -1;
}

// Den här metoden skapar ett unikt id för en klient.
int ReaderThread::createID(std::vector<Client*> *clients) {
	int id = 1;

	// Om det inte finns några klienter så låt den nya klienten få id 1.
	if (clients->size() == 0) {
		return id;
	// Om det redan finns klienter i vektorn så gå igenom alla för att hitta
	// ett unikt id som kan ges till den nyligen anslutna klienten.
	} else {
		bool idFound = true;
		while (idFound) {
			id++;
			idFound = false;
			for (int i = 0; i < clients->size(); i++) {
				if (clients->at(i)->getClientID() == id) {
					idFound = true;
				}
			}
		}
		return id;
	}
}

// Den här metoden skapar en position som det inte står någon annan klient på
// genom att gå igenom alla klienterna och kolla vad som är ledigt i x-led.
Coordinate ReaderThread::createPosition(std::vector<Client*> *clients) {
	std::cout << "Creating startposition...\n";
	Coordinate pos;
	// -100 är standard positionen.
	pos.x = -100;
	pos.y = -100;
	for (int i = 0; i < clients->size(); i++) {
		if (clients->at(i)->getPosition().x == pos.x && clients->at(i)->getPosition().y == pos.y &&
			clients->at(i)->getClientID() != clientID) {
			pos.x = pos.x + 1;
		}
	}
	return pos;
}

// Metod som kollar om en ny position är giltlig eller inte.
Coordinate ReaderThread::checkMove(int id, Coordinate newPosition, std::vector<Client*> *clients) {
	// Skapa en koordinat variabel och lagra -100 i både x och y.
	Coordinate oldPosition;
	oldPosition.x = -100;
	oldPosition.y = -100;
	
	// Gå igenom alla klienterna och kolla om klienten har någon gammala koordinater.
	// Om inte, så ge den -100, -100.
	bool empty = false;
	for (int i = 0; i < clients->size(); i++) {
		if (clients->at(i)->getClientID() == id) {
			if (clients->at(i)->getPosition().x == NULL) {
				empty = true;
			} else if (clients->at(i)->getPosition().y == NULL) {
				empty = true;
			} else {
				oldPosition = clients->at(i)->getPosition();
			}
		}
	}
	if (empty) {
		oldPosition = createPosition(clients);
	}

	// Kolla så att koordinaterna inte är utanför spelplanen.
	if (newPosition.x < -100 || newPosition.y < -100) {
		std::cout << "Coordinates are less than -100.\n";
		return oldPosition;
	}
	if (newPosition.x > 100 || newPosition.y > 100) {
		std::cout << "Coordinates are greater than 100.\n";
	}

	// Kolla sedan så att de nya koordinaterna inte är upptagna genom att loopa
	// igenom alla klienterna. Om platsen är upptagen så sätt flaggan isOccupied till true.
	bool isOccupied = false;
	for (int i = 0; i < clients->size(); i++) {
		if (clients->at(i)->getPosition().x == newPosition.x && clients->at(i)->getPosition().y == newPosition.y) {
			isOccupied = true;
			break;
		}
	}

	// Om de nya koordinaterna är upptagen så skicka de gamla koordinaterna.
	if (isOccupied) {
		std::cout << "Collision detected!\n";
		return oldPosition;
	} else {
		return newPosition;
	}
}

// Gå igenom alla klienterna och lagra de nya koordinaterna till klienten som har "id".
void updateClientPosition(int id, Coordinate pos, std::vector<Client*>* clients) {
	for (int i = 0; i < clients->size(); i++) {
		if (clients->at(i)->getClientID() == id) {
			clients->at(i)->setPosition(pos);
			std::cout << "Updated id: " << id << " with X: " << pos.x << " Y: " << pos.y << "\n";
		}
	}
}

// Ta bort en klient med "id".
void ReaderThread::removeClient(int id, std::vector<Client*> *clients) {
	for (int i = 0; i < clients->size(); i++) {
		if (clients->at(i)->getClientID() == id) {
			clients->erase(clients->begin() + i);
			std::cout << "Client id: " << id << " is removed.\n";
		}
	}
}

// Den huvudsakliga loopen som ska köras i en tråd.
void ReaderThread::operator()(Broadcaster *broad) {
	std::cout << "ReaderThread starting...\n";
	int recvbuflen = 1024;
	int iResult;

	char recvbuf[1024];
	do {
		iResult = recv(RecvSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			MsgHead* msgHead;
			printf("Bytes received: %d\n", iResult);
			msgHead = (MsgHead*)recvbuf;

			// När en klient ansluter, skapa ett unikt id och position och skicka det till alla klienter.
			if (msgHead->type == Join) {
				std::cout << "JOIN RECIEVED!\n";
				broad->incrementSeq();
				std::cout << "seq in readerthread is now: " << broad->getSeq();
				JoinMsg join;
				
				// Skapa ett unikt id.
				clientID = createID(broad->getClients());
				join.head.id = clientID;
				
				// Sätt meddelandetyp till "Join".
				join.head.type = Join;
				
				// Plussa på seq med 1.
				broad->incrementSeq();
				join.head.seq_no = broad->getSeq();
				
				// Ange storleken på meddelandet.
				join.head.length = sizeof(join);

				// Skapa en ny klient med det unika idet.
				Client* tmpclient = new Client(clientID, RecvSocket);
				
				// Lägg till klienten i vektorn.
				broad->getClients()->push_back(tmpclient);
				std::cout << "Sending ID: " << join.head.id << "\n";
				std::cout << "SEQ in ReaderThread is now: " << broad->getSeq() << "\n";
				
				// Skicka meddelandet till alla klienterna.
				broad->SendMessageToAll((char*)&join, sizeof(join));

				// Skapa ett nytt meddelande som informerar alla klienterna att
				// en ny klient har anslutit.
				ChangeMsg newPlayer;
				newPlayer.head.id = clientID;
				broad->incrementSeq();
				newPlayer.head.seq_no = broad->getSeq();
				newPlayer.head.type = Change;
				newPlayer.type = NewPlayer;

				std::cout << "SEQ in ReaderThread is now: " << broad->getSeq() << "\n";

				// Skicka det ovan nämnda meddelande till alla.
				broad->SendMessageToAll((char*)&newPlayer, sizeof(newPlayer));

				// Skapa ett nytt meddelande som anger den nyligen anslutna klientens
				// unika position.
				NewPlayerPositionMsg newPosition;
				
				// Skapa en unik position.
				newPosition.pos = createPosition(broad->getClients());
				std::cout << "Populating header...\n";
				
				// Fyll all nödvändig data i meddelandet.
				newPosition.msg.type = NewPlayerPosition;
				newPosition.msg.head.id = clientID;
				broad->incrementSeq();
				newPosition.msg.head.seq_no = broad->getSeq();
				newPosition.msg.head.type = Change;
				std::cout << "Sending startposition to client id: " << clientID << " \n";
				
				// Uppdatera klientens position i vektorn med sparade klienter.
				updateClientPosition(newPosition.msg.head.id, newPosition.pos, broad->getClients());

				std::cout << "SEQ in ReaderThread is now: " << broad->getSeq() << "\n";
				
				// Skicka meddelandet till alla.
				broad->SendMessageToAll((char*)&newPosition, sizeof(newPosition));

			} else if (msgHead->type == Leave) {
				std::cout << "LEAVE RECIEVED!\n";
				broad->incrementSeq();
				
				// När en klient skickar ett "Leave" meddelande till servern
				// så skapa ett meddelande om att klienten har lämnat spelen.
				ChangeMsg playerLeave;
				playerLeave.type = PlayerLeave;
				playerLeave.head.id = msgHead->id;
				broad->incrementSeq();
				playerLeave.head.seq_no = broad->getSeq();
				playerLeave.head.type = Change;

				std::cout << "SEQ in ReaderThread is now: " << broad->getSeq() << "\n";
				
				// Skicka meddelandet till alla klienterna.
				broad->SendMessageToAll((char*)&playerLeave, sizeof(playerLeave));

				removeClient(msgHead->id, broad->getClients());
				std::cout << "Removed client id: " << msgHead->id << "\n";
			} else if (msgHead->type == Event) {
				std::cout << "EVENT RECIEVED!\n";
				broad->incrementSeq();
				
				// När en klient skickar ett "MoveEvent" så kollar server om dem
				// nya koordinaterna är tomma och sedan uppdaterar klientens position
				// för att sedan meddela alla klienterna om den nya positionen.
				MoveEvent* moveEvent;
				moveEvent = (MoveEvent*)recvbuf;

				NewPlayerPositionMsg newPosition;
				newPosition.pos = checkMove(moveEvent->event.head.id, moveEvent->pos, broad->getClients());
				newPosition.msg.type = NewPlayerPosition;
				newPosition.msg.head.id = moveEvent->event.head.id;
				broad->incrementSeq();
				newPosition.msg.head.seq_no = broad->getSeq();
				newPosition.msg.head.type = Change;

				std::cout << "Client id: " << newPosition.msg.head.id << " moves to X: " << newPosition.pos.x << " Y: " << newPosition.pos.y << "\n";
				updateClientPosition(newPosition.msg.head.id, newPosition.pos, broad->getClients());

				std::cout << "SEQ in ReaderThread is now: " << broad->getSeq() << "\n";
				broad->SendMessageToAll((char*)&newPosition, sizeof(newPosition));
			}
		} else if (iResult == 0) {
			printf("Connection closed\n");
		} else {
			// Om klienten stänger anslutningen genom att stänga av programmet
			// så meddelar servern alla klienterna om att en klient med visst
			// id har lämnat spelet.
			ChangeMsg playerLeave;
			playerLeave.type = PlayerLeave;
			playerLeave.head.id = clientID;
			broad->incrementSeq();
			playerLeave.head.seq_no = broad->getSeq();
			playerLeave.head.type = Change;

			std::cout << "SEQ in ReaderThread is now: " << broad->getSeq() << "\n";
			broad->SendLeave((char*)&playerLeave, sizeof(playerLeave), clientID);
			//broad->SendMessageToAll((char*)&playerLeave, sizeof(playerLeave));

			// Remove the disconnected client from the clients vector.
			removeClient(clientID, broad->getClients());
			std::cout << "Removed client id: " << clientID << "\n";
		}
	} while (iResult > 0);
}
