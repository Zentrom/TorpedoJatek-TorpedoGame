#pragma once

#include "MenuRenderer.h"

#include "../../../Utility/gVertexBuffer.h"
#include <GL/glew.h>

#include <vector>
#include <string>

//Men� egy �llapot�t nyilv�ntart� oszt�ly
class MenuStateHandler 
{
public:
	MenuStateHandler();
	~MenuStateHandler();
	void Clean();

	void PreProcess();
	void Render(float pointed_element);

	void AddDecoratorTexture(float ndc_x, float ndc_y, float size_x, float size_y, GLuint texture);
	void AddDecoratorString(float ndc_x, float ndc_y, float size_x, const char* text);
	void AddButton(float ndc_x, float ndc_y, const char* name);
	void AddInputBox(const char* name);
	void BuildLayout();
	void UpdateInputBox(int id, const char* next_char, bool is_delete, bool is_cursor);

	std::vector<std::string> getInputStrings(int count);
private:

	MenuRenderer* menuRenderer = new MenuRenderer(); //Sz�vegek text�r�ba rajzol�sa
	gVertexBuffer vb_decorator; //Nem klikkelhet�k modell adatok
	gVertexBuffer vb_clickable; //Klikkelhet� modell adatok
	gShaderProgram sh_menu; //Men� shadere
	std::vector<GLuint> decoratorTextures; //Nem klikkelhet� objektumok text�r�ja
	std::vector<std::pair<std::string, GLuint>> clickableTextures; //Klikkelhet� objektumok sz�vege �s text�r�ja

	const size_t inputSizeLimit = 16; //Inputboxba maximum h�ny karaktert lehet �rni
	const int preProcessOffset = 100; //3D pickinghez offset hogy ne 0-t�l induljon

	float nextElementY = 0.4f; //Men� k�vi elem�t Y tengelyen hova rakjuk
};