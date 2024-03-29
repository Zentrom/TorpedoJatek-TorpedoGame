#pragma once

#include <SDL_ttf.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

#include <vector>
#include <iostream>

//Men� sz�veg�nek kirajzol� oszt�lya
class MenuRenderer {
public:
	MenuRenderer();
	~MenuRenderer();

	GLuint RenderTextSolid(const char* text);
	GLuint RenderTextShaded(const char* text);
private:
	TTF_Font* comicSans = nullptr; //Bet�t�pus adat
	TTF_Font* candara = nullptr; //Bet�t�pus adat

	SDL_PixelFormat* pixelFormat = nullptr; //Pixelform�tum amelybe konvert�ljuk az SDL Surface-t,hogy OPENGL ismerje
	SDL_Surface* textSurface = nullptr; //SDL_ttf ebbe a fel�letbe tudja a sz�veget kirajzolni
	GLuint textTexture = 0; //Sz�vegmez� OPENGL-es text�r�ja
	SDL_Color fgColor = { 255, 255, 255 }; //Sz�veg sz�ne
	SDL_Color bgColor = { 255, 0, 0 }; //Shaded rajzol�shoz a h�tt�rsz�n(Fragment shader nagyr�sz�t eldobja)
	glm::vec3 bgColorNDC = glm::vec3(0.0f); //Fragment shadernek,hogy ott 0-1 k�z�tt legyen az �rt�k
};