#include "FixProtocolManager.h"


FixProtocolManager::FixProtocolManager() {
	this->messageBuffer = this->currentPos = NULL;
    this->m_recvMsgSeqNumber = 1;
    this->m_sendMsgSeqNumber = 1;
	this->intConverter = new ItoaConverter();
	this->doubleConverter = new DtoaConverter();
	this->timeConverter = new UTCTimeConverter();
	this->currentTime = new SYSTEMTIME;
    for(int i = 0; i < this->m_maxRecvMessageCount; i++) {
        this->m_recvMessage[i] = new FixProtocolMessage(this->intConverter, this->timeConverter, this->doubleConverter);
    }
    this->m_recvMessageCount = 0;
}

FixProtocolManager::~FixProtocolManager() {
    delete this->intConverter;
    delete this->doubleConverter;
    delete this->timeConverter;
    delete this->currentTime;
}
