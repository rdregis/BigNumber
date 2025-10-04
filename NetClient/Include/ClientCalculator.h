#pragma once

#ifndef _CLIENTCALCULATOR_H_
#define _CLIENTCALCULATOR_H_

//**************************************************************************************
//*
//*		Info:
//*
//*		Date: AAAA/MM/DD
//*		Author: Rogerio Regis
//*
//*************************************************************************************

#define WIN32_LEAN_AND_MEAN

#define _WINSOCKAPI_    // stops windows.h including winsock.h
#include <winsock2.h>
#include <windows.h>

#include <string>
#include <sstream>
#include <iostream>
#include <memory>

#include "NetClient.h"



namespace NET
{
	//**************************************************************************************
	//*
	//*		Interface iClientCalculator
	//*
	//*************************************************************************************

	class IClientCalculator
	{
	public:
		using Pointer = std::unique_ptr<IClientCalculator>;
		virtual ~IClientCalculator() = default;


	};
}
namespace NET
{

	//**************************************************************************************
	//*	
	//*		class ClientCalculator
	//*
	//*************************************************************************************
	class ClientCalculator
		: public IClientCalculator
	{
	public:
		using Pointer = std::shared_ptr<ClientCalculator>;

		template<typename ...Args>
		Pointer static create(Args &&...arg)
		{
			struct EnaleMakeShared
				: public ClientCalculator
			{
				EnaleMakeShared(Args &&...arg)
					: ClientCalculator(std::forward<Args>(arg)...)
				{}
			};
			Pointer result(std::make_unique<EnaleMakeShared>(std::forward<Args>(arg)...));
			return(std::move(result));
		}
		virtual ~ClientCalculator() = default;


		ClientCalculator(const ClientCalculator&) = delete;
		ClientCalculator(ClientCalculator&&) = delete;
		const ClientCalculator& operator=(const ClientCalculator&) = delete;

		void connectToServer(const std::string& host, const std::string& port)
		{
			netClient_ = NET::NetClient::create();

			try {
				netClient_->connect(host, atoi(port.c_str()));
			}
			catch (const std::exception& ex) {
				std::stringstream ss;
				ss << "Client: Error: " << ex.what() << std::endl;
				throw(std::exception(ss.str().c_str()));
			}
		}
	

		const std::string sendToServer(const std::string& line)
		{
			char recvbuf[DEFAULT_BUFLEN + 1];
			int sizeReceived = 0;

			try {
				netClient_->sendSocket(line);
				sizeReceived = netClient_->receiveSocket(recvbuf);
			}
			catch (const std::exception& ex) {
				std::stringstream ss;
				ss << "Client: Error on Sender: " << ex.what() << std::endl;
				throw(std::exception(ss.str().c_str()));
			}

			std::string bytesReceived(recvbuf, sizeReceived);
			std::cout << "Client: Received from server: " << bytesReceived << std::endl;

			return(std::move(bytesReceived));
		}
		void disconnect()
		{
			netClient_->shutdown();
			netClient_->close();
		}

	public:
		explicit ClientCalculator()
		{
		}
	private:
		NET::NetClient::Pointer netClient_;
	};
}


#endif // !_NEWCLASS_H_

