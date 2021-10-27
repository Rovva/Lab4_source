/**
* Klassen som upprättar en socket som klienter kan ansluta till.
* @file SocketSetup.h
* @author Christoffer Rova
* @version 1.0
* @date 2021-10-26
*/

#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#ifndef MESSAGES_H
#define MESSAGES_H
#include "Messages.h"
#endif

class SocketSetup {
private:
	int RecvSocket;
	sockaddr_in server;
public:
	/**
	*	Konstruktor som skapar en socket.
	*/
	SocketSetup();
	
	/**
	*	Den här metoden returnerar den socket som skapats förut.
	*/
	int getSocket();
	
	/**
	*	Denna metod returnerar adress och port data.
	*/
	struct sockaddr_in getServer();
};
