#ifndef _GAME_H_
#define _GAME_H_
#include "Player.h"
#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/SocketAddress.h"
#include <fstream>
#include <iostream>
#include <map>
class Game
{
public: 
	Game(std::string address);
	~Game();

	void addPlayer(std::string player_name, int x, int y, int size, Poco::Net::SocketAddress addr);
	void removePlayer(std::string player_name);
	bool findPlayer(std::string find_player);

	
	void updateNet();

	void run();



private:
	std::map<std::string, Player> players;

	char buffer[23]; // 4(seq) + 4(x) + 4(y) + 1(quantity players in game) + 10(player nickname)   
	Poco::Net::DatagramSocket socket;
	Poco::Net::SocketAddress address;

	int last_seq;
	int seq;

};
#endif 
