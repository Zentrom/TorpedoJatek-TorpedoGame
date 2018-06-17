
#include "GameLogic.h"

#include "../../Utils/gCamera.h"
#include "../../Utils/gShaderProgram.h"


GameLogic::GameLogic(void)
{
	//for (int i = 0; i < activeTileCount; i++) {
	//	activeTiles[i] = 0;
	//}
}

GameLogic::~GameLogic(void)
{
}

void GameLogic::Init()
{
	std::cout << this->output << std::endl << std::endl;

	this->ConnectionSetup();

	//this->PlaceShips();
}


void GameLogic::ConnectionSetup()
{
	this->output = "Establishing connection.";
	std::cout << this->output << std::endl;

	this->output = "Server ip:";
	std::cout << this->output << std::endl;
	//std::cin >> this->ip;

	this->output = "Server port:";
	std::cout << this->output << std::endl;
	//std::cin >> this->port;
}

void GameLogic::PlaceShips()
{
	this->output = "Place your ships!/nChoose what kind of ship do you want to place down:";
	
	do {
		std::cout << std::endl <<
			this->output << std::endl
			<< "1. - 3tile ships left: " << this->ship3count << std::endl
			<< "2. - 2tile ships left: " << this->ship2count << std::endl
			<< "3. - 1tile ships left: " << this->ship1count << std::endl;

		std::cin >> this->choice;

		int tmpTile;
		std::string tmpBack[4] = {" "," "," "," "};
		int tmpMiddle[4] = { 0,0,0,0 };
		switch (choice) {
		case 1:
			if (ship3count != 0) {
				std::cout << this->shipFPlaceText << std::endl;
				std::cin >> this->shipFront;

				if (CheckString(this->shipFront)) {
					tmpTile = ProcessString(this->shipFront);

					if (CheckTile(tmpTile)) {

						if (TileProcessable(tmpTile + 10) && TileProcessable(tmpTile + 20)) {
							if (CheckTile(tmpTile + 10) && CheckTile(tmpTile + 20))
								tmpBack[0] = ProcessTile(tmpTile + 20);
								tmpMiddle[0] = tmpTile + 10;
						}
						if (TileProcessable(tmpTile - 10) && TileProcessable(tmpTile - 20)) {
							if (CheckTile(tmpTile - 10) && CheckTile(tmpTile - 20))
								tmpBack[1] = ProcessTile(tmpTile - 20);
								tmpMiddle[1] = tmpTile - 10;
						}
						if (TileProcessable(tmpTile + 1) && TileProcessable(tmpTile + 2)) {
							if (CheckTile(tmpTile + 1) && CheckTile(tmpTile + 2))
								tmpBack[2] = ProcessTile(tmpTile + 2);
								tmpMiddle[2] = tmpTile + 1;
						}
						if (TileProcessable(tmpTile - 1) && TileProcessable(tmpTile - 2)) {
							if (CheckTile(tmpTile - 1) && CheckTile(tmpTile - 2))
								tmpBack[3] = ProcessTile(tmpTile - 2);
								tmpMiddle[3] = tmpTile - 1;
						}

						bool tmpFound = false;
						int midIndex = 0;
						do {
							std::cout << this->shipBPlaceText << tmpBack[0] << tmpBack[1] << tmpBack[2] << tmpBack[3] << std::endl;
							std::cin >> this->shipBack;


							for (int i = 0; i < 4; i++) {
								if (this->shipBack == tmpBack[i]) {
									tmpFound = true;
									midIndex = i;
									break;
								}
							}
						} while (!tmpFound);

						for (int i = 0; i < this->activeTileCount; i++) {
							if (this->activeTiles[i] == 0) {
								this->activeTiles[i] = tmpTile;
								break;
							}
						}
						tmpTile = ProcessString(this->shipBack);
						for (int i = 0; i < this->activeTileCount; i++) {
							if (this->activeTiles[i] == 0) {
								this->activeTiles[i] = tmpTile;
								break;
							}
						}
						for (int i = 0; i < this->activeTileCount; i++) {
							if (this->activeTiles[i] == 0) {
								this->activeTiles[i] = tmpMiddle[midIndex];
								break;
							}
						}
						ship3count--;
						for (int i = 0; i < 4; i++) {
							tmpBack[i] = " ";
							tmpMiddle[i] = 0;
						}
					}
				}
			}
			break;
		case 2:
			if (ship2count != 0) {
				std::cout << this->shipFPlaceText << std::endl;
				std::cin >> this->shipFront;

				if (CheckString(this->shipFront)) {
					tmpTile = ProcessString(this->shipFront);

					if (CheckTile(tmpTile)) {

						if (TileProcessable(tmpTile + 10)) {
							if (CheckTile(tmpTile + 10))
								tmpBack[0] = ProcessTile(tmpTile + 10);
						}
						if (TileProcessable(tmpTile - 10)) {
							if (CheckTile(tmpTile - 10))
								tmpBack[1] = ProcessTile(tmpTile - 10);
						}
						if (TileProcessable(tmpTile + 1)) {
							if (CheckTile(tmpTile + 1))
								tmpBack[2] = ProcessTile(tmpTile + 1);
						}
						if (TileProcessable(tmpTile - 1)) {
							if (CheckTile(tmpTile - 1))
								tmpBack[3] = ProcessTile(tmpTile - 1);
						}

						bool tmpFound = false;
						do {
							std::cout << this->shipBPlaceText<< tmpBack[0] << tmpBack[1] << tmpBack[2] << tmpBack[3] << std::endl;
							std::cin >> this->shipBack;

						
							for (int i = 0; i < 4; i++) {
								if(this->shipBack==tmpBack[i]){
									tmpFound= true;
									break;
								}
							}
						} while (!tmpFound);

						for (int i = 0; i < this->activeTileCount; i++) {
							if (this->activeTiles[i] == 0) {
								this->activeTiles[i] = tmpTile;
								break;
							}
						}
						tmpTile = ProcessString(this->shipBack);
						for (int i = 0; i < this->activeTileCount; i++) {
							if (this->activeTiles[i] == 0) {
								this->activeTiles[i] = tmpTile;
								break;
							}
						}
						ship2count--;
						tmpBack[0] = " ";
						tmpBack[1] = " ";
						tmpBack[2] = " ";
						tmpBack[3] = " ";
					}
				}
			}
			break;
		case 3:
			if (ship1count != 0) {
				std::cout << this->ship1PlaceText << std::endl;
				std::cin >> this->shipFront;

				this->shipBack = this->shipFront;
				if (CheckString(this->shipFront)) {
					tmpTile = ProcessString(this->shipFront);
					
					if (CheckTile(tmpTile)) {

						for (int i = 0; i < this->activeTileCount; i++) {
							if (this->activeTiles[i] == 0) {
								this->activeTiles[i] = tmpTile;
								break;
							}
						}
						ship1count--;
					}
				}
			}
			break;
		default:
			std::cout << "You need to choose between 1-3!" << std::endl;
			break;
		}

	} while (this->ship3count!=0 ||this->ship2count!=0 || this->ship1count!=0);
}

int* GameLogic::getActiveTiles()
{
	return activeTiles;
}

//converts errorless stringinput in tilecoords
int GameLogic::ProcessString(std::string coord)
{
	strcpy(this->coordShip,coord.c_str());

	int first;
	switch (this->coordShip[0]) {
	case 'a':
		first = 1;
		break;
	case 'b':
		first = 2;
		break;
	case 'c':
		first = 3;
		break;
	case 'd':
		first = 4;
		break;
	case 'e':
		first = 5;
		break;
	case 'f':
		first = 6;
		break;
	case 'g':
		first = 7;
		break;
	default:
		break;
	}


	int second = atoi(&coordShip[1]);

	int result = 100 + first * 10 + second;

	return result;
}

//check errors in shipcoord string input
bool GameLogic::CheckString(std::string coord)
{
	if (coord.length() != 2) {
		std::cout << "Incorrect length!(must be 2)" << std::endl;
		return false;
	}
	char tmp[2];
	strcpy(tmp,coord.c_str());

	std::cout << tmp[0] << tmp[1];

	if (tmp[0] != 'a' && tmp[0] != 'b' && tmp[0] != 'c' && tmp[0] != 'd' && tmp[0] != 'e' && tmp[0] != 'f' && tmp[0] != 'g') {
		std::cout << "Incorrect column!(must be a-g)" << std::endl;
		return false;
	}
	if (tmp[1] != '1' && tmp[1] != '2' && tmp[1] != '3' && tmp[1] != '4' && tmp[1] != '5' && tmp[1] != '6' && tmp[1] != '7') {
		std::cout << "Incorrect row!(must be 1-7)" << std::endl;
		return false;
	}

	return true;
}

//check if the tile is free
bool GameLogic::CheckTile(int tile)
{
	for (int i = 0; i < this->activeTileCount; i++) {
		if (this->activeTiles[i] == tile) {
			return false;
		}
	}
	return true;
}

//creates stringcoord out of tilecoord
std::string GameLogic::ProcessTile(int tile)
{
	int column = (tile % 100) / 10;
	int row = tile % 10;

	char col;
	switch (column) {
	case 1:
		col = 'a';
		break;
	case 2:
		col = 'b';
		break;
	case 3:
		col = 'c';
		break;
	case 4:
		col = 'd';
		break;
	case 5:
		col = 'e';
		break;
	case 6:
		col = 'f';
		break;
	case 7:
		col = 'g';
		break;
	}

	char rowC;
	itoa(row, &rowC,10);

	std::string result;
	result.push_back(col);
	result.push_back(row);

	return result;
}

//checks if tilecoord is legal
bool GameLogic::TileProcessable(int tile)
{

	if(tile>177 || tile< 111){
		return false;
	}

	return true;
}