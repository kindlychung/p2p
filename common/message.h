#ifndef _CXM_P2P_MESSAGE_H_
#define _CXM_P2P_MESSAGE_H_

#include <stdint.h>
#include <memory>

#include "udp.h"
#include "candidate.h"
#include "transceiver.h"

#define CLIENT_NAME_LENGTH 31

typedef enum {
	CXM_P2P_MESSAGE_UNKNOWN = 0,
	CXM_P2P_MESSAGE_LOGIN,
	CXM_P2P_MESSAGE_LOGIN_SUB,
	CXM_P2P_MESSAGE_LOGIN_REPLY,
	CXM_P2P_MESSAGE_LOGOUT,
	CXM_P2P_MESSAGE_LOGOUT_REPLY,
	CXM_P2P_MESSAGE_CONNECT,
	CXM_P2P_MESSAGE_REPLY_CONNECT,
	CXM_P2P_MESSAGE_DO_P2P_CONNECT,
	CXM_P2P_MESSAGE_REPLY_P2P_CONNECT,
	CXM_P2P_MESSAGE_USER_DATA,
	CXM_P2P_MESSAGE_SERVER_KEEP_ALIVE,
	CXM_P2P_MESSAGE_PEER_KEEP_ALIVE,
	CXM_P2P_MESSAGE_PEER_DISCONNECT,
	CXM_P2P_MESSAGE_COUNT // remain last
} CXM_P2P_MESSAGE_TYPE;

#if 0
typedef enum {
	CXM_P2P_ROLE_SERVER, // message send by p2p server
	CXM_P2P_ROLE_CLIENT, // message send from peer to p2p server
	CXM_P2P_ROLE_P2P // message send from peer to peer
} CXM_P2P_ROLE_T;
#endif

typedef enum {
    CXM_P2P_PEER_ROLE_MASTER, // caller
    CXM_P2P_PEER_ROLE_SLAVE // callee
} CXM_P2P_PEER_ROLE_T;

typedef enum {
	CXM_P2P_REPLY_RESULT_OK = 1,
	CXM_P2P_REPLY_RESULT_UNKNOWN_PEER
} CXM_P2P_REPLY_RESULT_T;

struct Message
{
	uint16_t type;
	// uint8_t role;

	Message()
	{
		memset(this, 0, sizeof(Message));
	}

	union {
		struct {
			char clientName[CLIENT_NAME_LENGTH + 1];
			union {
				struct {
					uint32_t clientPrivateIp;
					uint16_t clientPrivatePort;
				} login;
				struct {

				} logout;
				struct {
					char remoteName[CLIENT_NAME_LENGTH + 1];
				} connect;
				struct {
					uint32_t remoteIp;
					uint16_t remotePort;
                    uint16_t peerRole;
					char remoteName[CLIENT_NAME_LENGTH + 1];
				} replyConnect;
			} uc;
		} client;

		struct {
			union {
				uint16_t userDataLength;
				struct {
					char key[CLIENT_NAME_LENGTH + 1];
                    uint16_t myPrivatePort;
				} p2p;
				struct {
					char key[CLIENT_NAME_LENGTH + 1];
                    uint16_t yourPublicPort;
                    uint16_t yourPrivatePort;
				} p2pReply;
			} up;
		} p2p;
	} u;
};

int MessageValidate(const Message *pmsg);
#endif

