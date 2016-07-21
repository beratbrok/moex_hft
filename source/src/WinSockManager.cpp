#include <stdio.h>
#include <thread>
#include <cstring>
#include <netdb.h>
#include <unistd.h>
#include "WinSockManager.h"
#include "LogManager.h"
#include <arpa/inet.h>

WinSockManager::WinSockManager(ISocketBufferProvider *provider) {
	this->m_socket = -1;
	this->m_serverAddressLogIndex = LogMessageCode::lmcNone;
	this->m_bufferProvider = provider;
	this->m_recvBuffer = this->m_bufferProvider->RecvBuffer();
	this->m_sendBuffer = this->m_bufferProvider->SendBuffer();
}


WinSockManager::~WinSockManager() {
}

bool WinSockManager::Connect(char *server_address, unsigned short server_port, WinSockConnectionType connType) {
	this->m_serverAddressLogIndex = DefaultLogMessageProvider::Default->RegisterText(server_address);

	DefaultLogManager::Default->StartLog(LogMessageCode::lmcWinSockManager_Connect, this->m_serverAddressLogIndex);

    this->m_connected = false;
    this->m_socket = socket(AF_INET, connType == WinSockConnectionType::wsTCP? SOCK_STREAM: SOCK_DGRAM, 0);

	if (this->m_socket < 0) {
		DefaultLogManager::Default->EndLog(false, strerror(errno));
		return false;
	}

	bzero(&this->m_adress, sizeof(sockaddr_in));
    inet_pton(AF_INET, server_address, &(this->m_adress.sin_addr));
    this->m_adress.sin_family = AF_INET;
	this->m_adress.sin_port = htons(server_port);

	int result = connect(this->m_socket, (struct sockaddr*)&(this->m_adress), sizeof(this->m_adress));
	if(result < 0) {
        close(this->m_socket);
		DefaultLogManager::Default->EndLog(false, strerror(errno));
		return false;
	}

	DefaultLogManager::Default->EndLog(true);
	this->m_connected = true;
	return true;
}

bool WinSockManager::Disconnect() {
	DefaultLogManager::Default->StartLog(LogMessageCode::lmcWinSockManager_Close, this->m_serverAddressLogIndex);
    if(this->m_socket == -1) {
        DefaultLogManager::Default->EndLog(true);
        return true;
    }

    if(this->m_connected) {
        shutdown(this->m_socket, SHUT_RDWR);
        this->m_connected = false;
    }

	int result = close(this->m_socket);
	if (result != 0) {
		DefaultLogManager::Default->EndLog(false, strerror(errno));
		return false;
	}
	DefaultLogManager::Default->EndLog(true);
	return true;
}

void WinSockManager::Run()
{
	//std::thread tr = std::thread(&WinSockManager::RunCore, this);
}
void WinSockManager::RunCore() {
	/*
	std::thread tr = std::thread(&WinSockManager::ProcessMessageCore, this);
	char message[10000];
	while (true){
		int data_length = Recv(message, 10000);
		if (data_length <= 0) continue;

		unsigned int i = 0;
		while (i < (unsigned int)data_length)
		{
			char* res = &(message[i]);
			i += strlen(res);
			SetMessage(res);
		}
	}
	*/
}

bool WinSockManager::Reconnect() { 
	DefaultLogManager::Default->StartLog(LogMessageCode::lmcWinSockManager_Reconnect, this->m_serverAddressLogIndex);

    if(this->m_connected) {
        shutdown(this->m_socket, SHUT_RDWR);
        this->m_connected = false;
    }

    int result = close(this->m_socket);
	if (result < 0) {
		DefaultLogManager::Default->EndLog(false, strerror(errno));
		return false;
	}

    this->m_connected = false;
	this->m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->m_socket < 0) {
		DefaultLogManager::Default->EndLog(false, strerror(errno));
		return false;
	}
	
	result = connect(this->m_socket, (const sockaddr*)&(this->m_adress), sizeof(this->m_adress));
	if (result < 0) {
		DefaultLogManager::Default->EndLog(false, strerror(errno));
		return false;
	}

	DefaultLogManager::Default->EndLog(true);
	return true;
}

bool WinSockManager::TryFixSocketError(int errorCode) {

	return this->Reconnect();
}
