#pragma once

#ifndef _NETCLIENT_H_
#define _NETCLIENT_H_

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

	class INetClient
	{
	public:
		using Pointer = std::unique_ptr<INetClient>;
		virtual ~INetClient() = default;


	};
}
namespace NET
{

	//**************************************************************************************
	//*	
	//*		class NetClient
	//*
	//*************************************************************************************
	class NetClient
		: public INetClient, public Network
	{
	public:
		using Pointer = std::shared_ptr<NetClient>;
		using socklen_t = int;

		template<typename ...Args>
		Pointer static create(Args &&...arg)
		{
			struct EnaleMakeShared
				: public NetClient
			{
				EnaleMakeShared(Args &&...arg)
					: NetClient(std::forward<Args>(arg)...)
				{}
			};
			Pointer result(std::make_unique<EnaleMakeShared>(std::forward<Args>(arg)...));
			return(std::move(result));
		}
		virtual ~NetClient() = default;


		NetClient(const NetClient&) = delete;
		NetClient(NetClient&&) = delete;
		const NetClient& operator=(const NetClient&) = delete;

		void connect(const std::string& ipAdress, int port)
		{
			// Create a SOCKET for connecting to server
			
			connectSocket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (connectSocket_ == INVALID_SOCKET) {
				int lstError = WSAGetLastError();
				WSACleanup();
				std::stringstream ss;
				ss << "socket function failed with error : " << lstError;
				throw(std::exception(ss.str().c_str()));

			}
			
			// The sockaddr_in structure specifies the address family,
			// IP address, and port of the server to be connected to.
			sockaddr_in clientService;

			
			clientService.sin_family = AF_INET;
			clientService.sin_port = htons(port);
			clientService.sin_addr.s_addr = inet_addr(ipAdress.c_str());

			//inet_pton(AF_INET, ipAdress.c_str(), &(clientService));
			
			
			// Connect to server.
			int iResult = ::connect(connectSocket_, (SOCKADDR*)&clientService, sizeof(clientService));
			if (iResult == SOCKET_ERROR) {
				int lstError = WSAGetLastError();
				closesocket(connectSocket_);
				WSACleanup();

				std::stringstream ss;
				ss << "connect failed with error : " << lstError;
				throw(std::exception(ss.str().c_str()));
			}


			wprintf(L"Connected to server.\n");
		}




	private:
		explicit NetClient()
			: Network(connectSocket_)
		{
		}

	private:
		SOCKET connectSocket_;
	};

}




#endif // !_NEWCLASS_H_

