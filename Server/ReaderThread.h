/**
* Klassen som tar emot meddelanden och behandlar dessa.
* @file ReaderThread.h
* @author Christoffer Rova
* @version 1.0
* @date 2021-10-26
*/

#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <vector>
#include <thread>
#include "Broadcaster.h"
#include "Client.h"
#ifndef MESSAGES_H
#define MESSAGES_H
#include "Messages.h"
#endif

class ReaderThread {
private:
	int RecvSocket;
	int clientID;
public:
	/**
	*	Konstruktor som tar emot en socket som parameter och lagrar den lokalt.
	*/
	ReaderThread(int socket);
	
	/**
	*	Den här metoden skapar ett unikt id för en klient.
	*	@param[in]		*clients		Vektorn med alla klienterna.
	*	@param[out]		id				Unikt id.
	*/
	int createID(std::vector<Client*> *clients);
	
	/**
	*	Den här metoden skapar en position som är tom, d.v.s. där ingen spelare står genom att kolla vad som är ledigt i x-led.
	*	@param[in]		*clients		Vektorn med alla klienterna.
	*	@param[out]		pos				Unika koordinater.
	*/
	Coordinate createPosition(std::vector<Client*> *clients);
	
	/**
	*	Metod som kollar om en ny position är giltlig eller inte.
	*	@param[in]		id				Klientens id.
	*	@param[in]		*clients		Vektorn med alla klienter.
	*	@param[out]		pos				Giltliga koordinater.
	*/
	Coordinate checkMove(int id, Coordinate newPosition, std::vector<Client*> *clients);
	
	/**
	*	Gå igenom alla klienterna och lagra de nya koordinaterna till klienten som har "id".
	*	@param[in]		id				Klientens id.
	*	@param[in]		pos				Koordinaterna.
	*	@param[in]		*clients		Vektorn med alla klienter.
	*/
	updateClientPosition(int id, Coordinate pos, std::vector<Client*>* clients)
	
	/**
	*	Den här metoden tar bort en klient från spelet.
	*	@param[in]		id				Klienten som ska tas bort.
	*	@param[in]		*clients		Vektorn med alla klienter.
	*/
	void removeClient(int id, std::vector<Client*> *clients);
	
	/**
	*	Den huvudsakliga loopen som ska köras i en tråd och hantera alla meddelanden som kommer till servern.
	*	@param[in]		*broad			Referens till objektet Broadcaster.
	*/
	void operator()(Broadcaster *broad);
};
