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

	main-client.cpp
	Main source for console client application.
*/

#include "gpro-net/gpro-net-client/gpro-net-RakNet-Client.hpp"

#include "gpro-net/gpro-net.h"

#include <vector>

#include "../gpro-net-Client-Plugin/gpro-net-Client-Plugin.h"

#if (defined _WINDOWS || defined _WIN32)

//#include <Windows.h>
#pragma comment(lib, "gpro-net-Client-Plugin.lib")

// complete plugin test
int testPlugin()
{
	//HMODULE plugin = LoadLibrary(TEXT("./plugin/gpro-net-Client-Plugin"));
	//if (plugin)
	{
		printf("%d \n", foo(9000));

		// done
		//return FreeLibrary(plugin);
		return 1;
	}
	return -1;
}

#else	// !(defined _WINDOWS || defined _WIN32)

// dummy plugin test
int testPlugin()
{
	return -1;
}

#endif	// (defined _WINDOWS || defined _WIN32)

enum GameMessages
{
	ID_INCOMING_CONNECTION = ID_USER_PACKET_ENUM + 1,
	ID_JOIN_BATTLESHIP = ID_USER_PACKET_ENUM + 2,
	ID_JOIN_MANCALA = ID_USER_PACKET_ENUM + 3,
	ID_JOIN_CHECKERS = ID_USER_PACKET_ENUM + 4
};

struct PacketToSend
{
	std::string connectionName;
	GameMessages newMessage;
};


void recieveMessages(RakNet::Packet& incomingPacket, RakNet::RakPeerInterface& peer, PacketToSend& newPacket)
{
	for (incomingPacket = peer->Recieve(); incomingPacket; peer->DeallocatePacket(incomingPacket), incomingPacket = peer->Recieve())
	{
		switch (packet->data[0])
		{
		case ID_INCOMING_CONNECTION:
			// Get introductory message and print to screen
			break;
		case ID_JOIN_BATTLESHIP:
			// Create packet for desire to leave server for battleship
			break;
		case ID_JOIN_MANCALA:
			// Create packet for desire to leave server for mancala
			break;
		case ID_JOIN_CHECKERS:
			// Create packet for desire to leave server for checkers
			break;
		default:
			break;
		}
	}
}

std::vector<PacketToSend> checkForPlayerInput() 
{
	// check if player has pressed anything
	// If they have, then send a message accordingly 
}

void sendOutput(RakNet::RakPeerInterface& peer, PacketToSend& newPacket)
{
	// get said new packets and make a new message
	// Iterate through packets vector
	// take the contents of the new message and write it to a bitstream
	// send out message using peer
}



int main(int const argc, char const* const argv[])
{
	bool canShutdownServer = false;

	RakNet::RakPeerInterface* peer = RakNet::RakPeerInterface::GetInstance();
	RakNet::Packet* newPacket = NULL;

	std::vector<PacketToSend> newPacket;

	// Get IP address
	// checkif connection is right

	while (!canShutdownServer)
	{
		recieveInput(newPacket, peer, newPacket);
		newPacket = checkForPlayerInput();
		sendOutput(peer, newPacket);

		// Check for the escape bar
		// if escape has been hit, then leave the server
	}

	// disconnectfromallservers

	printf("\n\n");
	system("pause");
}
