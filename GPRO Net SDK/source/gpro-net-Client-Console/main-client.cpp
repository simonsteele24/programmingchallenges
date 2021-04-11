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

float GetMagnitude(float elements[3])
{
    return sqrt(pow(elements[0], 2) + pow(elements[1], 2) + pow(elements[2], 2));
}

char ConvertScaleToChar(float elementToBePutIn)
{
    return elementToBePutIn * 511 * sqrt(2);
}

float ConvertCharToScale(char compressedElement)
{
    return compressedElement * (1 / (511 * sqrt(2)));
}

char ConvertRotateToChar(float elementToBePutIn)
{
    return elementToBePutIn * 511 * sqrt(2);
}

float ConvertCharToRotate(char compressedElement)
{
    return compressedElement * (1 / (511 * sqrt(2)));
}

char ConvertTranslateToChar(float elementToBePutIn)
{
    return elementToBePutIn * 511 * sqrt(2);
}

float ConvertCharToTranslate(char compressedElement)
{
    return compressedElement * (1 / (511 * sqrt(2)));
}

struct sSpatialPose
{
    float scale[3];     // non-uniform scale
    float rotate[3];    // orientation as Euler angles
    float translate[3]; // translation

    // read from stream
    RakNet::BitStream& Read(RakNet::BitStream& bitstream)
    {
        char readBit;
        float magnitude;

        // scale
        bitstream.Read(magnitude);
        bitstream.Read(readBit);
        scale[0] = ConvertCharToScale(readBit) * magnitude;
        bitstream.Read(readBit);
        scale[1] = ConvertCharToScale(readBit) * magnitude;
        bitstream.Read(readBit);
        scale[2] = ConvertCharToScale(readBit) * magnitude;

        // rotate
        bitstream.Read(magnitude);
        bitstream.Read(readBit);
        rotate[0] = ConvertCharToRotate(readBit) * magnitude;
        bitstream.Read(readBit);
        rotate[1] = ConvertCharToRotate(readBit) * magnitude;
        bitstream.Read(readBit);
        rotate[2] = ConvertCharToRotate(readBit) * magnitude;

        // translate
        bitstream.Read(magnitude);
        bitstream.Read(readBit);
        translate[0] = ConvertCharToTranslate(readBit) * magnitude;
        bitstream.Read(readBit);
        translate[1] = ConvertCharToTranslate(readBit) * magnitude;
        bitstream.Read(readBit);
        translate[2] = ConvertCharToTranslate(readBit) * magnitude;

        return bitstream;
    }

    // write to stream
    RakNet::BitStream& Write(RakNet::BitStream& bitstream) const
    {
        // Scale
        float temp[3] = { scale[0],scale[1],scale[2] };
        float magnitude = GetMagnitude(temp);
        bitstream.Write(magnitude);

        bitstream.Write(ConvertScaleToChar(scale[0]) / magnitude);
        bitstream.Write(ConvertScaleToChar(scale[1]) / magnitude);
        bitstream.Write(ConvertScaleToChar(scale[2]) / magnitude);

        // Rotate
        float temp2[3] = { rotate[0],rotate[1],rotate[2] };
        magnitude = GetMagnitude(temp2);
        bitstream.Write(magnitude);

        bitstream.Write(ConvertRotateToChar(rotate[0]) / magnitude);
        bitstream.Write(ConvertRotateToChar(rotate[1]) / magnitude);
        bitstream.Write(ConvertRotateToChar(rotate[2]) / magnitude);


        // Translate
        float temp3[3] = { translate[0],translate[1],translate[2] };
        magnitude = GetMagnitude(temp3);
        bitstream.Write(magnitude);

        bitstream.Write(ConvertTranslateToChar(translate[0]) / magnitude);
        bitstream.Write(ConvertTranslateToChar(translate[1]) / magnitude);
        bitstream.Write(ConvertTranslateToChar(translate[2]) / magnitude);

        return bitstream;
    }
};

// utility test (game states, console)
int testUtility()
{
	gpro_battleship battleship;
	gpro_checkers checkers;
	gpro_mancala mancala;

	gpro_battleship_reset(battleship);
	gpro_checkers_reset(checkers);
	gpro_mancala_reset(mancala);

	return gpro_consoleDrawTestPatch();
}


int main(int const argc, char const* const argv[])
{
	testUtility();

	testPlugin();

	gproNet::cRakNetClient client;

	while (1)
	{
		client.MessageLoop();
	}

	printf("\n\n");
	system("pause");
}
