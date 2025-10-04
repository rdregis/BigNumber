#pragma once

#define WIN32_LEAN_AND_MEAN

#define _WINSOCKAPI_    // stops windows.h including winsock.h
#include <winsock2.h>
#include <windows.h>

#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include <chrono>
#include <exception>
#include <iomanip>

#include <stdio.h>
#include <stdlib.h>

#include "NetServer.h"

#include "BNExecutor.h"

const std::string processingMessage(BigNum::BNExecutor::Pointer bnExecutor, const std::string & bytesReceived)
{
	std::chrono::high_resolution_clock::time_point startTime_;
	std::chrono::high_resolution_clock::time_point stopTime_;

	
	std::cout << "Server: Receive from client:" << bytesReceived << std::endl;

	startTime_ = std::chrono::steady_clock::now();
	BigNum::MathBigNumber bnRstOper = bnExecutor->execute(bytesReceived);
	stopTime_ = std::chrono::steady_clock::now();

	
	std::stringstream ss;
	ss << "["
		<< std::setw(3) << std::setfill('0') << std::chrono::duration_cast<std::chrono::seconds>(stopTime_ - startTime_).count() << "."
		<< std::setw(7) << std::setfill('0') << (float)(std::chrono::duration_cast<std::chrono::microseconds>(stopTime_ - startTime_).count()) / 1000
		<< "];" << bytesReceived << "=" << (bnRstOper.getNumber() == "-0" ? "Error" : bnRstOper.getNumber()) << ";" << std::endl;

	return(std::move(ss.str()));
}

int main(int argc, char const* argv[])
{
	if (argc < 3) {
		std::cout << "Error: invalid parameter. Use " << argv[0] << " <host> <port>" << std::endl;
		return (-1);
	}
	std::cout << "Server Program executed: "
		<< argv[0] << " " << argv[1] << " " << argv[2]  << std::endl;

	const std::string host(argv[1]);
	const std::string port(argv[2]);

	NET::NetServer::Pointer netServer = NET::NetServer::create();

	try {
		netServer->initialize(host, atoi(port.c_str()));
	}
	catch (const std::exception& ex) {
		std::cout << "Server: Error: " << ex.what() << std::endl;
		return (-1);
	}

	BigNum::BNExecutor::Pointer bnExecutor = BigNum::BNExecutor::create();

	

	int sizeReceived;
	try {
		char recvbuf[DEFAULT_BUFLEN + 1];
		while ((sizeReceived = netServer->receiveSocket(recvbuf)) > 0) {
			std::string bytesReceived(recvbuf, sizeReceived);
			const std::string &msgToClient = processingMessage(bnExecutor, bytesReceived);
			netServer->sendSocket(msgToClient);
		}
	}
	catch (const std::exception& ex) {
		std::cout << "Server: Error: " << ex.what() << std::endl;
		return (-1);
	}

	netServer->shutdown();
	netServer->close();

	return(0);
}