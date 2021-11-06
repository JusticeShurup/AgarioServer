#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include <Poco/Net/SocketAddress.h>

struct Player
{
	Player();
	Player(std::string player_name, int x, int y, int size, Poco::Net::SocketAddress socket_address);
	int x; 
	int y;
	int size;
	std::string name;

	int last_seq;
	Poco::Net::SocketAddress socket_address;
};
#endif