#include "FormBigNumber.h"

const std::string sendToServer(NET::NetClient::Pointer netClient, const std::string& line)
{
	char recvbuf[DEFAULT_BUFLEN + 1];
	int sizeReceived = 0;

	try {
		netClient->sendSocket(line);
		sizeReceived = netClient->receiveSocket(recvbuf);
	}
	catch (const std::exception& ex) {
		std::cout << "Client: Error on Sender: " << ex.what() << std::endl;
	}

	std::string bytesReceived(recvbuf, sizeReceived);
	std::cout << "Client: Received from server: " << bytesReceived << std::endl;

	return(std::move(bytesReceived));
}