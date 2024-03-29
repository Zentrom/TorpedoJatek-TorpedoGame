#pragma once

//Glob�lis v�ltoz�k,amikre sok oszt�lyba sz�ks�g van
namespace TorpedoGLOBAL {
	const bool CameraBounds = true; //Legyen-e bekorl�tozva a kamera a j�t�kt�rre.
	const float Scale = 1.0f; //glob�lis grafikai sk�l�z�s
	extern bool Debug; //Ha ez igaz,akkor a kliens DEBUG m�dba fut,nem csatlakozik szerverhez. J� grafikai tesztel�skor. TorpedoJatekClient.cpp-ben defini�lva

	const float SeaTileScaleXZ = 2.0f; //Tengermez� nagy�t�s
}

//J�t�k kliens �llapota
enum GameState {
	INITIAL = 1,
	SHIP_SIZE_INPUT,
	PLACING_SHIP,
	STARTING_MATCH,
	SHOOTING_AT_ENEMY,
	GETTING_SHOT,
	CHECKING_VICTORY_CONDITION,
	MATCH_ENDING,
};

//Men� milyen signalt k�ld a kezel� oszt�lynak
enum MenuSignal {
	CONTINUE = 1,
	CONNECT,
	DEBUG,
	QUIT,
};
