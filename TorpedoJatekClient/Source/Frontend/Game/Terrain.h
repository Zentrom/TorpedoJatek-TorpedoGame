#pragma once

#include "../../Globals.hpp"

#include "../../../Utility/gVertexBuffer.h"
#include "../../../Utility/gShaderProgram.h"
#include "../../../Utility/gCamera.h"
#include "../../../Utility/GLUtils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

//A F�ld ter�let oszt�lya
class Terrain
{
public:
	Terrain(int seatile_row_count, float mountain_height_y);
	~Terrain();

	void Init();
	void Draw(const gCamera& camera, gShaderProgram& sh_program) const;

	const int getTerrainScale() const;
	const float getGroundScaleXZ() const;

private:
	void CalcGroundTileTransformations();

	gVertexBuffer vb_terrain; //grafikai adatokat t�rol� buffer
	GLuint groundTextureID; //f�lddarab text�ra azonos�t�ja
	std::vector<glm::vec3> groundTileTrans; //f�lddarabok elmozgaz�sai

	const int terrainScale = 50; //A terrainscale az feldarabolja az ugyanolyan nagy n�gyzetet

	const float groundScaleToSeaTile; //Tengermez�h�z k�pest mekkor�t sk�l�zunk
	const float groundMountainY; //hegy k�zepe �s alja k�zti t�v
	const int terrainSizeXZ; //h�ny darab f�lddarab legyen
	const glm::mat4 matWorld; //vil�g transzform�ci�
	const glm::mat4 matWorldIT; //VT inverze
	const float groundScaleXZ; //f�lddarab sk�l�z�sa XZ tengelyeken

};
