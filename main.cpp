#include <Poco/Net/DatagramSocket.h>
#include <Poco/Net/SocketAddress.h>
#include <iostream>

int main() {
	float coordinates[2] = {300, 300};
	int seq = 1;
	int last_seq = 0;
	Poco::Net::SocketAddress address_server("127.0.0.1:1337");
	Poco::Net::DatagramSocket socket;
	socket.bind(address_server);
	Poco::Net::SocketAddress addr;
	float dX = 0, dY = 0;
	int seq_new = 0;
	while (true) {
		float data[3] = {seq, coordinates[0], coordinates[1]};
		float receive_data[3] = { seq_new, dX, dY };
		socket.receiveFrom(receive_data, sizeof(float) * 3, addr);
		if (last_seq < int(receive_data[0])) {
			last_seq = int(receive_data[0]);
			coordinates[0] += receive_data[1];
			coordinates[1] += receive_data[2];
		}
		std::cout << data[0] << " " << data[1] << " " << data[2] << std::endl;
		socket.sendTo(data, sizeof(float) * 3, addr);
		seq++;
	}
}