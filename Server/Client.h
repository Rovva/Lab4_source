/**
* Klassen som hanterar klienter.
* @file Client.h
* @author Christoffer Rova
* @version 1.0
* @date 2021-10-26
*/
#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

#ifndef MESSAGES_H
#define MESSAGES_H
#include "Messages.h"
#endif
#include <thread>

class Client {
private:
	int clientID;
	Coordinate position;
	int clientSocket;
public:
	/**
	*	Konstruktor som tar emot ID och socket.
	*	@param[in]		id		Klient-id.
	*	@param[in]		socket	Klientens socket.
	*/
	Client(int id, int socket);
	
	/**
	*	Den här metoden returnerar klientens id.
	*/
	int getClientID();
	
	/**
	*	Den här metoden returnerar klientens position.
	*/
	Coordinate getPosition();
	
	/**
	*	Denna metod ändrar klientens position.
	*/
	void setPosition(Coordinate newPosition);
	
	/**
	*	Denna metod returnerar klientens socket.
	*/
	int getSocket();
};
