#pragma once

#ifndef _NETSERVER_H_
#define _NETSERVER_H_

//**************************************************************************************
//*
//*		Info:
//*
//*		Date: AAAA/MM/DD
//*		Author: Rogerio Regis
//*
//*************************************************************************************


#include <string>
#include <sstream>
#include <iostream>
#include <memory>

#include "Network.h"


namespace NET
{
	//**************************************************************************************
	//*
	//*		Interface INewClass
	//*
	//*************************************************************************************

	class INetServer
	{
	public:
		using Pointer = std::unique_ptr<INetServer>;
		virtual ~INetServer() = default;


	};
}
namespace NET
{

	//**************************************************************************************
	//*	
	//*		class NetServer
	//*
	//*************************************************************************************
	class NetServer
		: public INetServer, public Network
	{
	public:
		using Pointer = std::shared_ptr<NetServer>;
		using socklen_t = int;

		template<typename ...Args>
		Pointer static create(Args &&...arg)
		{
			struct EnaleMakeShared
				: public NetServer
			{
				EnaleMakeShared(Args &&...arg)
					: NetServer(std::forward<Args>(arg)...)
				{}
			};
			Pointer result(std::make_unique<EnaleMakeShared>(std::forward<Args>(arg)...));
			return(std::move(result));
		}
		virtual ~NetServer() = default;


		NetServer(const NetServer&) = delete;
		NetServer(NetServer&&) = delete;
		const NetServer& operator=(const NetServer&) = delete;

		void initialize(const std::string& ipAdress, int port)
		{

			//----------------------
			// Create a SOCKET for listening for
			// incoming connection requests.
			
			listenSocket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (listenSocket_ == INVALID_SOCKET) {
				int lstError = WSAGetLastError();
				WSACleanup();
				std::stringstream ss;
				ss << "socket failed with error : " << lstError;
				throw(std::exception(ss.str().c_str()));
			}
			//----------------------
			// The sockaddr_in structure specifies the address family,
			// IP address, and port for the socket that is being bound.
			sockaddr_in service;
			service.sin_family = AF_INET;
			service.sin_port = htons(port);
			service.sin_addr.s_addr = inet_addr(ipAdress.c_str());
			//inet_pton(AF_INET, ipAdress.c_str(), &(service));
			
			if (bind(listenSocket_, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
				std::stringstream ss;
				ss << "bind failed with error: " << WSAGetLastError();
				closesocket(listenSocket_);
				WSACleanup();
				throw(std::exception(ss.str().c_str()));
			}
			//----------------------
			// Listen for incoming connection requests.
			// on the created socket
			if (listen(listenSocket_, 1) == SOCKET_ERROR) {
				std::stringstream ss;
				ss << "listen failed with error: " << WSAGetLastError();
				closesocket(listenSocket_);
				WSACleanup();
				throw(std::exception(ss.str().c_str()));

			}
			//----------------------
			// Create a SOCKET for accepting incoming requests.
			
			std::cout << "Waiting for client to connect..." << std::endl;

			//----------------------
			// Accept the connection.
			acceptSocket_ = accept(listenSocket_, NULL, NULL)	;
			if (acceptSocket_ == INVALID_SOCKET) {
				std::stringstream ss;
				ss << "accept failed with error: " << WSAGetLastError();
				closesocket(listenSocket_);
				WSACleanup();
				throw(std::exception(ss.str().c_str()));
			}
			


			std::cout << "Client connected." << std::endl;

		}

	

	private:
		explicit NetServer()
			: Network(acceptSocket_)
		{
		}



	private:
		SOCKET listenSocket_;
		SOCKET acceptSocket_;
	};
}


#endif // !_NEWCLASS_H_

