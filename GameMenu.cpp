#include "stdafx.h"
#include "GameMenu.h"
#include "TileTextures.h"
#include <gl\GLAux.h>

extern TileTextures tails;
extern double mx;		//мышьикс
extern double my;		//мышьигрик
int flagMenu = 1;

GameMenu::GameMenu()
{
}


GameMenu::~GameMenu()
{
}

void GameMenu::Draw()
{
	glBindTexture(GL_TEXTURE_2D, tails.textures[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(0, 0);
	glTexCoord2f(0.0, 1.0); glVertex2f(0 ,800);
	glTexCoord2f(1.0, 1.0); glVertex2f(800,800);
	glTexCoord2f(1.0, 0.0); glVertex2f(800,0);
	glEnd();


}