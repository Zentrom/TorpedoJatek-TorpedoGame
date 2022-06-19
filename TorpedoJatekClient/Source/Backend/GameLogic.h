#pragma once

#include "ClientHandler.h"
#include "../Frontend/Fleet.h"
#include "../Frontend/Sea.h"
#include "../Globals.hpp"

#include "../../Utility/gVertexBuffer.h"
#include "../../Utility/gShaderProgram.h"
#include "../../Utility/gCamera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <array>
#include <algorithm>

//J�t�k h�tt�rlogik�j�val kapcsolatos oszt�ly
class GameLogic
{
public:
	GameLogic(void);
	~GameLogic(void);

	int Init(Fleet*& player, Fleet*& enemy, Sea*& sea);
	void ConnectionSetup();
	void InitGame();
	void DisplayMessage(GameState gameState, int related_data);
	void DisplayError(GameState gameState, int related_data);
	bool CheckForUnplacedShips(int shipSize);
	bool CheckAnyUnplacedShipLeft();
	bool PlaceShip(int tileIndex, int shipSize);
	void SendFleetToServer();

	bool CheckStartSignal();
	void StopGame();

	PlayTile* Shoot(int tileindex);
	PlayTile* GetShoot();
	int CheckVictoryState();

	int getPlayerNum();
protected:
	ClientHandler clientHandler;	//A h�l�zati kapcsolat kliens-oldali vez�rl�je

	//Debug m�dban be�getett dolgok
	void PlaceShipsINDEBUG();
	void SetTilesINDEBUG();

	bool CheckString(std::string coord);
	//PlayTile ProcessString(std::string coord);
	std::string ProcessTile(const std::pair<char, int> &tile);
	bool TileProcessable(const std::pair<char, int> &tile);
	int ConvertCoordToTileIndex(const std::pair<char, int> &tile);

	std::string output = "Torpedo Jatek";

	PlayTile *shipFront; //Haj� elej�t foglal� mez�
	PlayTile *shipBack; //Haj� h�t�t foglal� mez�
	bool shipFrontPlaced = false; //Leraktuk-e m�r egy haj� elej�t
	std::array<PlayTile*, 4> freeChoices; //Haj� h�t�nak megfelel� poz�ci�k

	std::string ip = "127.0.0.1";	//A szerver-ip sz�veges alakja
	int port = 27015; //szerver port

	Fleet *myFleet;	//Pointer a mi haj�sereg�nkre
	Fleet *enemyFleet;	//Pointer az ellenf�l haj�sereg�re
	Sea *mySea;	//Pointer a tengerre

	std::array<int, 4> &unplacedShips = std::array<int, 4>(); //H�ny haj� nincs m�g lerakva(k�l�n m�retekben)

	int mapSize = 7;	//T�rolt p�lyam�ret DEBUG m�dhoz
	int choice = 0; //Felhaszn�l�i input,mikor d�nteni kell

	int playerNum;	//Ha 1 akkor mi kezd�nk,ha 2 akkor nem

	ResponseState matchState = ResponseState::START_OF_GAME; //Szerverrel val� kommunik�ci� f�zisa
};