/**
* Klassen som skickar data till servern.
* @file WriterThread.h
* @author Christoffer Rova
* @version 1.0
* @date 2021-10-26
*/

#pragma once
#ifndef MESSAGES_H

#define MESSAGES_H

#include "Messages.h"

#endif 
#ifdef _WIN32
#include <Winsock2.h>
#endif
#include <ws2tcpip.h>
#include <stdio.h>
#include <thread>
#include <iostream>

class WriterThread {
private:
	SOCKET ConnectSocket;
public:
	/**
	*	Konstruktor som tar emot en socket som lagras lokalt i klassen.
	*/
	WriterThread(SOCKET socket);
	
	/**
	*	Metoden som ska köras om och om igen i en tråd.
	*/
	void operator()();
	
	/**
	*	Den här metoden skickar "Join" meddelande till servern.
	*/
	void sendJoin();
	
	/**
	*	Den här metoden skickar ett "Leave" meddelande till servern.
	*	param[in]	id	Klient-id
	*/
	void sendLeave(int id);
	
	/**
	*	Denna metod skickar ett "MoveEvent" meddelande till servern.
	*	param[in]	id			Klient-id
	*	param[in]	position	Koordinater
	*	param[in]	*seq		Sekvensnummer
	*/
	void sendMoveEvent(int id, Coordinate position, int *seq);
};