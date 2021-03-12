/*
   Copyright 2021 Daniel S. Buckstein

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

/*
	GPRO Net SDK: Networking framework.
	By Daniel S. Buckstein

	main-server.cpp
	Main source for console server application.
*/

#include "gpro-net/gpro-net-server/gpro-net-RakNet-Server.hpp"
#include "gpro-net/gpro-net.h"
#include "RakNet/MessageIdentifiers.h"
#include "RakNet/RakPeerInterface.h"
#include "RakNet/BitStream.h"
#include "RakNet/RakNetTypes.h"

#include <string>

using namespace RakNet;

enum GameMessages
{
	ID_INCOMING_CONNECTION = ID_USER_PACKET_ENUM + 1,
	ID_JOIN_BATTLESHIP = ID_USER_PACKET_ENUM + 2,
	ID_JOIN_MANCALA = ID_USER_PACKET_ENUM + 3,
	ID_JOIN_CHECKERS = ID_USER_PACKET_ENUM + 4
};

struct User 
{
	std::string connectionName;
	std::string userName;
};

struct PacketToSend 
{
	std::string connectionName;
		GameMessages newMessage;
};

void recieveUserInput(RakNet::Packet & incomingPacket, RakNet::RakPeerInterface & peer,PacketToSend & newPacket) 
{
	for (incomingPacket = peer->Recieve(); incomingPacket; peer->DeallocatePacket(incomingPacket), incomingPacket = peer->Recieve()) 
	{
		switch (packet->data[0])
		{
		case ID_INCOMING_CONNECTION:
			// Add user to connection
			// Add user to vector array
			// Create packet that will send the introductory messages to that user
			break;
		case ID_JOIN_BATTLESHIP:
			// disconnect user from the user array
			// create a packet that will make the user join the battleship server
			break;
		case ID_JOIN_MANCALA:
			// disconnect user from the user array
			// create a packet that will make the user join the mancala server
			break;
		case ID_JOIN_CHECKERS:
			// disconnect user from the user array
			// create a packet that will make the user join the checkers server
			break;
		default:
			break;
		}
	}
}

void sendOutput(RakNet::RakPeerInterface& peer, PacketToSend& newPacket)
{
	// get said new packet and make a new message
	// take the contents of the new message and write it to a bitstream
	// send out message using peer
}

int main(int const argc, char const* const argv[])
{
	bool canShutdownServer = false;

	gproNet::cRakNetServer server;

	RakNet::RakPeerInterface* peer = RakNet::RakPeerInterface::GetInstance();
	RakNet::Packet* newPacket = NULL;

	PacketToSend newPacket;

	SocketDescriptor socket(1000, 0);

	peer->Startup(10, &socket, 1);

	while (!canShutdownServer)
	{
		recieveUserInput(newPacket, peer, newPacket);
		sendOutput(peer,newPacket);

		// Check for the escape bar
		// if escape has been hit, then leave the server
	}

	peer->Shutdown();

	printf("\n\n");
	system("pause");
}
