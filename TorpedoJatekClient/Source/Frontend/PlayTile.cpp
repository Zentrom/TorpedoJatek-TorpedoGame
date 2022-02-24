
#include "PlayTile.h"

PlayTile::PlayTile(void)
{
}

PlayTile::PlayTile(const std::pair<char, int> &pos) : position(pos)
{
}

PlayTile::~PlayTile(void)
{
}

//J�t�kmez� index�t rajzoljuk ki az alpha sz�ncsatorn�ba
void PlayTile::PreProcess(gCamera &camera, gShaderProgram &sh_program)
{
	glm::mat4 matWorld = glm::translate(seatile_translate) * glm::rotate(seatile_rotate, seatile_rotate_angle) * glm::scale(seatile_scale);
	glm::mat4 matWorldIT = glm::transpose(glm::inverse(matWorld));
	glm::mat4 mvp = camera.GetViewProj() *matWorld;

	sh_program.SetUniform("world", matWorld);
	sh_program.SetUniform("worldIT", matWorldIT);
	sh_program.SetUniform("MVP", mvp);
	sh_program.SetUniform("is_preprocess", true);
	sh_program.SetUniform("tile_index", index + indexOffset);

	vb_seatile.On();
	vb_seatile.DrawIndexed(GL_TRIANGLES, 0, 6, 0);
	vb_seatile.Off();
}

//Egy j�t�kmez� kirajzol�sa
void PlayTile::Draw(gCamera &camera, gShaderProgram &sh_program, GLuint &textureID)
{

	glm::mat4 matWorld = glm::translate(seatile_translate) * glm::rotate(seatile_rotate, seatile_rotate_angle) * glm::scale(seatile_scale - outlineWidth);
	glm::mat4 matWorldIT = glm::transpose(glm::inverse(matWorld));
	glm::mat4 mvp = camera.GetViewProj() *matWorld;

	sh_program.SetUniform("world", matWorld);
	sh_program.SetUniform("worldIT", matWorldIT);
	sh_program.SetUniform("MVP", mvp);
	sh_program.SetUniform("is_seatile", true);
	sh_program.SetUniform("tilestate_changed", isStateChanged);
	sh_program.SetUniform("tile_state", tileState);

	sh_program.SetUniform("hasTexture", true);
	sh_program.SetTexture("texImage", 0, textureID);

	vb_seatile.On();
	vb_seatile.DrawIndexed(GL_TRIANGLES, 0, 6, 0);
	vb_seatile.Off();

	sh_program.SetUniform("hasTexture", false);
	sh_program.SetUniform("is_seatile", false);
	sh_program.SetUniform("tilestate_changed", false);
}

//K�rvonalakat rajzolja ki a j�t�kmez�k k�r�
void PlayTile::OutlineDraw(gCamera &camera, gShaderProgram &sh_program)
{
	glm::mat4 matWorld = glm::translate(seatile_translate) * glm::rotate(seatile_rotate, seatile_rotate_angle) * glm::scale(seatile_scale);
	glm::mat4 matWorldIT = glm::transpose(glm::inverse(matWorld));
	glm::mat4 mvp = camera.GetViewProj() *matWorld;

	sh_program.SetUniform("world", matWorld);
	sh_program.SetUniform("worldIT", matWorldIT);
	sh_program.SetUniform("MVP", mvp);
	sh_program.SetUniform("is_preprocess", false);
	sh_program.SetUniform("tile_state", tileState);
	sh_program.SetUniform("tile_index", index + indexOffset);

	vb_seatile.On();
	vb_seatile.DrawIndexed(GL_TRIANGLES, 0, 6, 0);
	vb_seatile.Off();
}

//J�t�kmez� �llapot�nak �ll�t�sa(hogy m�s sz�ne legyen)
void PlayTile::setState(int newState)
{
	isStateChanged = true;
	switch (newState) {
	case 1: //hit
		tileState = glm::vec3(1, 0, 0);
		break;
	case 2: //miss
		if (tileState.x != 1 || tileState.y != 0 || tileState.z != 0) {
			tileState = glm::vec3(1, 1, 0);
		}
		break;
	case 3: //default
		tileState = glm::vec3(1, 1, 1);
		isStateChanged = false;
		break;
	case 4: //winPlayerOne
		tileState = glm::vec3(1, 0, 0);
		break;
	case 5: //winPlayerTwo
		tileState = glm::vec3(1, 0, 0);
		break;
	case 6: //Back of the ship placeable here
		tileState = glm::vec3(0, 1, 0);
		break;
	case 7: //Cursor selection color
		tileState = glm::vec3(0, 1, 1);
		break;
	default:
		tileState = glm::vec3(0, 0, 1);
		break;
	}
}

void PlayTile::setIndex(int newIndex)
{
	index = newIndex;
}

void PlayTile::setUsed(bool used)
{
	usedTile = used;
}

//Kinull�zza a j�t�kmez� koordin�t�j�t
void PlayTile::ClearPosition()
{
	position = std::pair<char, int>('0', 0);
}

int PlayTile::getIndex() const
{
	return index;
}

std::pair<char, int> PlayTile::getPos() const
{
	return position;
}

//Van-e haj� a mez�n
bool PlayTile::isUsed() const
{
	return usedTile;
}

glm::vec3 PlayTile::getTranslate() const
{
	return seatile_translate;
}

int PlayTile::getIndexOffset() const
{
	return indexOffset;
}

glm::vec3 PlayTile::getState() const
{
	return tileState;
}
