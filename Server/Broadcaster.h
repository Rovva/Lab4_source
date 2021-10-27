/**
* Klassen som skickar meddelanden till alla anslutna klienter.
* @file Broadcaster.h
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
#include "Client.h"

class Broadcaster {
private:
	std::vector<Client*>* clients;
	int seq;
public:
	/**
	*	Konstruktor som tar emot en vektor som lagras lokalt i klassen.
	*/
	Broadcaster(std::vector<Client*>* clientVector);
	
	/**
	*	Den här metoden returnerar vektorn med klienter.
	*	@param[out]		clients		Vektorn med klienter.
	*/
	std::vector<Client*>* getClients();
	
	/**
	*	Denna metod returnerar sekvensnummret.
	*	@param[out]		seq		Aktuella sekvensnummret.
	*/
	int getSeq();
	
	/**
	*	Metoden ökar sekvensnummret med 1.
	*/
	void incrementSeq();
	
	/**
	*	Den här metoden skickar meddelande till alla anslutna klienter.
	*	@param[in]		buffer		Meddelandet som ska skickas.
	*	@param[in]		size		Storlek på meddelandet.
	*/
	void SendMessageToAll(char* buffer, int size);
	
	/**
	*	Denna metod skickar ett "Leave" meddelande till alla klienter utom den som lämnar spelet.
	*	@param[in]		buffer		Meddelandet.
	*	@param[in]		size		Storlek på meddelandet.
	*	@param[in]		clientID	Klientens id som lämnar spelet.
	*/
	void SendLeave(char* buffer, int size, int clientID);
};
