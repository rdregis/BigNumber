#pragma once

#ifndef _NETWORK_H_
#define _NETWORK_H_

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
#include <exception>

//#define WIN32_LEAN_AND_MEAN
//
//#define _WINSOCKAPI_    // stops windows.h including winsock.h
////#include <winsock2.h>
//#include <windows.h>



#define DEFAULT_BUFLEN 1024



namespace NET
{
	//**************************************************************************************
	//*
	//*		Interface INetwork
	//*
	//*************************************************************************************

	class INetwork
	{
	public:
		using Pointer = std::unique_ptr<INetwork>;
		virtual ~INetwork() = default;


	};
}
namespace NET
{

	//**************************************************************************************
	//*	
	//*		class IceServer
	//*
	//*************************************************************************************
	class Network
		: public INetwork
	{
	public:
		using Pointer = std::unique_ptr<Network>;

		template<typename ...Args>
		Pointer static create(Args &&...arg)
		{
			struct EnaleMakeShared
				: public Network
			{
				EnaleMakeShared(Args &&...arg)
					: Network(std::forward<Args>(arg)...)
				{}
			};
			Pointer result(std::make_unique<EnaleMakeShared>(std::forward<Args>(arg)...));
			return(std::move(result));
		}
		virtual ~Network() = default;


		Network(const Network&) = delete;
		Network(Network&&) = delete;
		const Network& operator=(const Network&) = delete;

		int sendSocket(const std::string& toSend)
		{
			int iResult;

			// Send an initial buffer
			iResult = send(netSocket_, toSend.c_str(), (int)toSend.size(), 0);
			if (iResult == SOCKET_ERROR) {
				std::stringstream ss;
				ss << "send failed with error : " << WSAGetLastError();
				WSACleanup();
				throw(std::exception(ss.str().c_str()));
			}

			std::cout << "Bytes Sent: " << iResult << std::endl;
			return(iResult);
		}

		int receiveSocket(char* recvbuf)
		{

			int recvbuflen = DEFAULT_BUFLEN;

			int iResult = recv(netSocket_, recvbuf, recvbuflen, 0);
			if (iResult < 0) {
				std::stringstream ss;
				ss << "recv failed with error : " << WSAGetLastError();
				WSACleanup();
				throw(std::exception(ss.str().c_str()));
			}

			std::cout << "Bytes received: " << iResult << std::endl;
			if (iResult == 0) {
				std::cout << "Connection closed" << iResult << std::endl;
			}

			return (iResult);
		}

		void shutdown()
		{
			int iResult;

			iResult = ::shutdown(netSocket_, SD_SEND);

			if (iResult == SOCKET_ERROR) {
				std::stringstream ss;
				ss << "shutdown function failed with error : " << WSAGetLastError();
				WSACleanup();
				throw(std::exception(ss.str().c_str()));
			}
		}

		void close()
		{
			int iResult;


			iResult = closesocket(netSocket_);

			if (iResult == SOCKET_ERROR) {
				std::stringstream ss;
				ss << "closesocket function failed with error : " << WSAGetLastError();
				WSACleanup();
				throw(std::exception(ss.str().c_str()));
			}

			WSACleanup();
		}


	protected:
		explicit Network(SOCKET& netSocket)
			: netSocket_(netSocket)
		{

			// Initialize Winsock
			WSADATA wsaData;

			int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
			if (iResult != NO_ERROR) {
				std::stringstream ss;
				ss << "WSAStartup function failed with error : " << iResult;
				throw(std::exception(ss.str().c_str()));
			}
		}


	private:
		SOCKET& netSocket_;
	};
}


#endif // !_NEWCLASS_H_

