#include <iostream>
#include "TorpedoJatekServer.h"

int main(int argc, char* args[]) {

	std::cout << "TorpedoJatekServer was compiled on (" << __DATE__ 
		<<") with compiler value " << __cplusplus << std::endl;

	TorpedoJatekServer torpedoServer;
	
	return torpedoServer.Start();

}