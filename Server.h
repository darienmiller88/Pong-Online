#pragma once
#include <SFML/Network.hpp>
#include <unordered_map>

using user = std::pair<uint16_t, sf::IpAddress>;

class Server{
	public:
		Server(uint16_t portToListen);
		void runServer();
	private:
		sf::UdpSocket serverSocket;
		std::unordered_map<int, user> users;
};

