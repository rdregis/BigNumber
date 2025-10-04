#pragma once



#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include <exception>
#include <filesystem>

#include <fstream>

#include <stdio.h>
#include <stdlib.h>


#include "ClientCalculator.h"



int main(int argc, char const* argv[])
{

	if (argc < 5) {
		std::cout << "Error: invalid parameter. Use " << argv[0] << " <host> <port> <input file> <output file>"  << std::endl;
		return (-1);
	}
	std::cout << "Client Program executed: " 
		<< argv[0] << " " << argv[1] << " " << argv[2] << " " << argv[3] << " " << argv[4] << std::endl;

	const std::string host(argv[1]);
	const std::string port(argv[2]);
	const std::string inFilename(argv[3]);
	const std::string outFilename(argv[4]);

	
	if ((!std::filesystem::exists(inFilename)) ||
		(!std::filesystem::is_regular_file(inFilename))) {
		std::cout << "File : " << inFilename << " not exist" << std::endl;
		return (-1);
	}


	NET::ClientCalculator::Pointer netClient = NET::ClientCalculator::create();

	try {
		netClient->connectToServer(host, port);
	}
	catch (const std::exception& ex) {
		std::cout << "Client: Error: " << ex.what() << std::endl;
		return (-1);
	}


	std::ifstream fileIn(inFilename);

	if (fileIn.is_open()) {
		std::ofstream fileOut(outFilename);
		std::string line;

		while (std::getline(fileIn, line)) {
			std::cout << "Client: Send to server: " << line << std::endl;
			try {
				const std::string& bytesReceived = netClient->sendToServer(line);
				fileOut.write(bytesReceived.c_str(), bytesReceived.size());
			}
			catch (const std::exception& ex) {
				std::cout << "Client: Error: " << ex.what() << std::endl;
				return (-1);
			}
		}
		fileIn.close();
	}
	netClient->disconnect();

	return(0);
}