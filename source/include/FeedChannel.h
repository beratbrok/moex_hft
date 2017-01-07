#pragma once
#include "FeedConnections.h"

class FeedChannel {
	char id[16];
	int  m_idLogIndex;
	char name[64];
	int  m_nameLogIndex;
	const char *m_senderCompId;
	const char *m_password;

	FeedConnection *statisticsIncremental;
	FeedConnection *statisticsSnapshot;
	FeedConnection *ordersIncremental;
	FeedConnection *ordersSnapshot;
	FeedConnection *tradesIncremental;
	FeedConnection *tradesSnapshot;
	FeedConnection *instrumentDefinition;
	FeedConnection *instrumentStatus;
	FeedConnection *historicalReplay;

	bool CheckConnections();

public:
	FeedChannel(const char *id, const char *name);
	~FeedChannel();

	void SetPassword(const char *password) {
		this->m_password = password;
		if(this->statisticsIncremental != NULL)
			this->statisticsIncremental->SetPassword(this->m_password);
		if(this->statisticsSnapshot != NULL)
			this->statisticsSnapshot->SetPassword(this->m_password);
		if(this->ordersIncremental != NULL)
			this->ordersIncremental->SetPassword(this->m_password);
		if(this->ordersSnapshot != NULL)
			this->ordersSnapshot->SetPassword(this->m_password);
		if(this->tradesIncremental != NULL)
			this->tradesIncremental->SetPassword(this->m_password);
		if(this->tradesSnapshot != NULL)
			this->tradesSnapshot->SetPassword(this->m_password);
		if(this->instrumentDefinition != NULL)
			this->instrumentDefinition->SetPassword(this->m_password);
		if(this->instrumentStatus != NULL)
			this->instrumentStatus->SetPassword(this->m_password);
		if(this->historicalReplay != NULL)
			this->historicalReplay->SetPassword(this->m_password);
	}

	void SetSenderCompId(const char *senderCompId) {
		this->m_senderCompId = senderCompId;

		if(this->statisticsIncremental != NULL)
			this->statisticsIncremental->SetSenderCompId(this->m_senderCompId);
		if(this->statisticsSnapshot != NULL)
			this->statisticsSnapshot->SetSenderCompId(this->m_senderCompId);
		if(this->ordersIncremental != NULL)
			this->ordersIncremental->SetSenderCompId(this->m_senderCompId);
		if(this->ordersSnapshot != NULL)
			this->ordersSnapshot->SetSenderCompId(this->m_senderCompId);
		if(this->tradesIncremental != NULL)
			this->tradesIncremental->SetSenderCompId(this->m_senderCompId);
		if(this->tradesSnapshot != NULL)
			this->tradesSnapshot->SetSenderCompId(this->m_senderCompId);
		if(this->instrumentDefinition != NULL)
			this->instrumentDefinition->SetSenderCompId(this->m_senderCompId);
		if(this->instrumentStatus != NULL)
			this->instrumentStatus->SetSenderCompId(this->m_senderCompId);
		if(this->historicalReplay != NULL)
			this->historicalReplay->SetSenderCompId(this->m_senderCompId);
	}

	void SetConnection(FeedConnection *conn);
	const char* Id() { return this->id; }
	const char* Name() { return this->name; }

	bool Connect(FeedConnection *conn);
	bool Disconnect(FeedConnection *conn);
	bool Connect();
	bool Disconnect();
	bool Logon(FeedConnection *conn);
	bool Logout(FeedConnection *conn);
	bool Logon();
	bool Logout();

	inline bool DoWorkAtom() {
		bool res = this->statisticsIncremental->DoWorkAtom();
		res &= this->statisticsSnapshot->DoWorkAtom();
		res &= this->ordersIncremental->DoWorkAtom();
		res &= this->ordersSnapshot->DoWorkAtom();
		res &= this->tradesIncremental->DoWorkAtom();
		res &= this->tradesSnapshot->DoWorkAtom();
		res &= this->instrumentDefinition->DoWorkAtom();
		res &= this->instrumentStatus->DoWorkAtom();
		res &= this->historicalReplay->DoWorkAtom();

		return res;
	}
};

