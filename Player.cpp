#include "Player.h"
Player::Player() {};

Player::Player(std::string player_name, int x, int y, int size, Poco::Net::SocketAddress addr) :
	socket_address(addr)
{
	name = player_name;
	this->x = x;
	this->y = y;
	this->size = size;
	this->last_seq = 0;
}