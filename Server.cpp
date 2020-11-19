#include "Server.h"
#include <iostream>

Server::Server(uint16_t portToListen){
	if (serverSocket.bind(portToListen) != sf::Socket::Done) {
		std::cout << "Could not bind to port: " << portToListen << ":C Terminating program!\n";
		exit(1);
	}
}

void Server::runServer(){
	sf::IpAddress ip;
	uint16_t port;
	sf::Packet receivePacket;
}
