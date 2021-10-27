/**
* Klassen som tar emot anslutningar.
* @file ConnectionThread.h
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
#include "ReaderThread.h"
#include "Broadcaster.h"
#ifndef MESSAGES_H
#define MESSAGES_H
#include "Messages.h"
#endif

class ConnectionThread {
private:
	int RecvSocket;
	sockaddr_in server;
public:
// Konstruktorn tar emot en socket och sockaddr som är nödvändigt för att 
// etablera och upprätthålla anslutningar till klienter.
	/**
	*	Konstruktorn tar emot en socket och sockaddr som är nödvändigt för att etablera och upprätthålla anslutningar till klienter.
	*	@param[in]		*socket		Socket som tar emot anslutningar.
	*	@param[in]		srv			
	*/
	ConnectionThread(int *socket, sockaddr_in srv);
	
	/**
	*	Den här metoden ska köras om och om igen i en tråd. Dess uppgift är att ta emot anslutningar från klienter.
	*/
	void operator()(Broadcaster *broad, int *seq);
};
