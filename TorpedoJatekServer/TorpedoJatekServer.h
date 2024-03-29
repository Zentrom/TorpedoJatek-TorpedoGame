#pragma once

#include "Source/ServerHandler.h"
#include "../CommonSource/TorpedoVersion.hpp"
#include "../CommonSource/CommonGlobals.hpp"

#include <SDL.h>
#include <SDL_net.h>

#include <iostream>
#include <cstring>
#include <utility>
#include <vector>
#include <array>
#include <sstream>

//Szerver f�oszt�lya
class TorpedoJatekServer
{
public:
	TorpedoJatekServer();
	~TorpedoJatekServer();

	bool Run();

private:
	//Melyik szerveropci�
	enum class SetupOptions {
		CLOSE_PROGRAM,
		START_SERVER,
		CHANGE_MAPSIZE,
		CHANGE_PORT,
		DUMMY_OPTION = 9999,
	};

	//A szerver "p�rhuzamos�t�s�hoz" el kell t�rolni,hogy hol tartottunk egy klienssel
	enum class ClientState {
		NOT_CONNECTED,
		RECEIVING_SHIPS,
		IN_MATCH_SHOOTER,
		IN_MATCH_TAKER,
	};

	//Haj�adatok
	struct ShipTile {
		explicit ShipTile(std::pair<char, int> til) {
			tileCoord = til;
		}

		std::pair<char, int> tileCoord; //Haj� mez�koordin�t�ja
		bool isIntact = true; //Nincs-e m�g kil�ve
	};

	//Kliensadatok
	struct Client {
		std::stringstream name; //n�v
		int playerNum; //h�nyadik j�t�kos
		TCPsocket socket; //kapcsolati socket
		std::vector<std::vector<ShipTile> > ships; //Haj�k adatai
		int unreadTiles; //H�ny haj�s mez�t kell m�g �tk�ldj�n a kliens
		ClientState state = ClientState::NOT_CONNECTED; //Az elej�n a kliens m�g nem csatlakozott
	}firstClient, secondClient, temporaryClient;

	void Init();
	void DisplaySettings();
	void AllocateShips();
	void PrepareMatch();
	void HandleClientState(Client& client);
	bool CheckClientVersion(TCPsocket& connected_socket);
	void StartMatch();
	void HandleShot(Client& shooter, Client& taker);
	ResponseState ProcessTiles(Client& client);
	void SendShipsToLoser(Client& client);
	int getFirstNotConnectedIndex() const;

	std::array<Client*, 3> clients; //Csatlakozott kliensek pointer t�mbje
	const TorpedoVersion* serverVersion = new TorpedoVersion(); //szerver verzi�sz�ma

	IPaddress ip; //ip oszt�lya
	Uint16 port = 27015; //portsz�m
	SDLNet_SocketSet socketSet = nullptr; //socket csoport
	TCPsocket server = nullptr; //szerver socket
	const int maxSockets = 4; //maximum h�ny socket lehet egy socketcsoportban
	int connectedPlayers = 0; //H�ny j�t�kos csatlakozott - Temp connectiont lesz�m�tva

	std::stringstream currentSettings; //Jelenlegi be�ll�t�sok sz�vegesen
	ResponseState responseState = ResponseState::START_OF_GAME; //Mi a j�t�k �llapota
	MessageType receivedType; //Elv�rt �zenetet k�ld-e a kliens

	std::string input; //Inputot t�rol� string
	int mapSize = 5; //j�t�kP�lya m�rete
	int shipCount; //H�ny haj� lesz
	int activeTileCount; //H�ny akt�v mez� lesz
	bool isDisconnection = false; //Valamelyik j�t�kos kil�pett-e
	std::pair<char, int> targetTile; //melyik mez�koordin�t�ra l�tt valaki

};
