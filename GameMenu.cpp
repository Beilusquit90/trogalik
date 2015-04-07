#include "stdafx.h"
#include "GameMenu.h"
#include "TileTextures.h"
#include <gl\GLAux.h>
#include <iostream>
#include "Shambala.h"
extern double mx;		//мышьикс
extern double my;		//мышьигрик
extern Shambala x;
Shambala *xx = &x;

extern TileTextures tails;
int flagMenu = 1;

GameMenu::GameMenu()
{
}


GameMenu::~GameMenu()
{
}

int GameMenu::sKeyboard(unsigned char keyx, int x, int y)
{
	return 0;
}


void GameMenu::Keyboard(unsigned char keyx, int x, int y)
{
		switch (keyx)
		{
		case 27:flagMenu = 0; break;
		case'r':xx->Restart();flagMenu=0; break;
		case'q': exit(0); break;
		default: std::cout<<"'default' bottom in menu..." << std::endl; break;
		}
}

void GameMenu::Draw()
{
	//std::cout << "DrawMenu" << std::endl;
	glBindTexture(GL_TEXTURE_2D, tails.textures[7]);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0, 0.0); glVertex2f(0, 0);
	glTexCoord2f(0.0, 1.0); glVertex2f(0 ,800);
	glTexCoord2f(1.0, 1.0); glVertex2f(800,800);
	glTexCoord2f(1.0, 0.0); glVertex2f(800,0);
	glEnd();
}
