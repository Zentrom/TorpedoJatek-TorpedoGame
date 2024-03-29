#pragma once

#include "Ship.h"
#include "BShipCannon.h"

//Egy l�v� haj�
class BattleShip : public Ship
{
public:
	BattleShip(const glm::vec3& battle_ship_translate, bool ally);
	~BattleShip();

	void Draw(const gCamera& camera, gShaderProgram& sh_program, const gVertexBuffer& vb_ship, const gVertexBuffer& vb_flag);
	void ResetForDEBUG();
	const BShipCannon& getCannon() const;
private:
	BShipCannon* cannon = nullptr; //�gy�
};