#include "Game.h"

Game::Game(std::string address) :
	address(address), 
	buffer{0}
{
	socket.bind(this->address);
	last_seq = 0;
	seq = 1;
}

Game::~Game(){}

void Game::addPlayer(std::string player_name, int x, int y, int size, Poco::Net::SocketAddress addr) {
	players.insert(std::pair<std::string, Player>(player_name, Player(player_name, x, y, size, addr)));
}

void Game::removePlayer(std::string player_name) {
	players.erase(player_name);
}

bool Game::findPlayer(std::string player_name) {
	auto search = players.find(player_name);
	if (search != players.end()) {
		return true;
	}
	else {
		return false;
	}
}

void Game::updateNet() {
	
	std::string player_name;
	
	int x = 200;
	int y = 200;
	socket.receiveFrom(buffer, 22, address);
	player_name = std::string(buffer + 12);
	if (!findPlayer(player_name)) {
		std::cout << player_name << std::endl;
		addPlayer(player_name, x, y, 100, address);
	}
	int receive_seq = *((uint32_t*)buffer);
	if (receive_seq > players[player_name].last_seq) {
		players[player_name].last_seq = receive_seq;
		players[player_name].x = *((int*)buffer + 1);
		players[player_name].y = *((int*)buffer + 2);
	}


	*((uint32_t*)buffer) = seq;
	*((int*)buffer + 1) = players[player_name].x;
	*((int*)buffer + 2) = players[player_name].y;
	*((uint8_t*)buffer + 3) = players.size();
	strcpy(buffer + sizeof(int) * 3, player_name.c_str());
	socket.sendTo(buffer, 23, address);
	
	for (auto it = players.begin(); it != players.end(); it++) {
		if (it->second.name != player_name) {
			*((uint32_t*)buffer) = seq;
			*((int*)buffer + 1) = it->second.x;
			*((int*)buffer + 2) = it->second.y;
			strcpy(buffer + sizeof(int) * 3, it->second.name.c_str());
			socket.sendTo(buffer, 22, address);
		}
	}
	seq++;
}

void Game::run() {
	while (true) {
		updateNet();
	}
}

