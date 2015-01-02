#include "stdafx.h"
#include "TileTextures.h"
#include <gl\glaux.h>
#include <iostream>
TileTextures tails;
double mx;
double my;


TileTextures::TileTextures()
{
}


TileTextures::~TileTextures()
{
}

void TileTextures::LoadTextures()
{
	AUX_RGBImageRec *texture1 = auxDIBImageLoadA("1.bmp");
	AUX_RGBImageRec *texture2 = auxDIBImageLoadA("2.bmp"); // оставлю на будущее...
	AUX_RGBImageRec *texture3 = auxDIBImageLoadA("3.bmp");
	AUX_RGBImageRec *texture4 = auxDIBImageLoadA("4.bmp");
	AUX_RGBImageRec *texture5 = auxDIBImageLoadA("5.bmp");
	AUX_RGBImageRec *texture6 = auxDIBImageLoadA("6.bmp");
	AUX_RGBImageRec *texture7 = auxDIBImageLoadA("7.bmp");
	AUX_RGBImageRec *menu = auxDIBImageLoadA("Menu.bmp");
	AUX_RGBImageRec *bowman = auxDIBImageLoadA("bowman.bmp");


	glGenTextures(9, &textures[0]);		// первый элемент, сколько загружаем текстур. второй ссылка, на первый элемент массива

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture2->sizeX, texture2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2->data);

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture3->sizeX, texture3->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture3->data);

	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture4->sizeX, texture4->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture4->data);

	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture5->sizeX, texture5->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture5->data);

	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture6->sizeX, texture6->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture6->data);

	glBindTexture(GL_TEXTURE_2D, textures[6]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture7->sizeX, texture7->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture7->data);

	glBindTexture(GL_TEXTURE_2D, textures[7]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, menu->sizeX, menu->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, menu->data);

	glBindTexture(GL_TEXTURE_2D, textures[8]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, bowman->sizeX, bowman->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, bowman->data);
}

void TileTextures::DrawMouse()
{
	/*glBindTexture(GL_TEXTURE_2D, tails.textures[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(mx - 15, my);
	glTexCoord2f(0.0, 1.0); glVertex2f(mx - 15,my + 15);
	glTexCoord2f(1.0, 1.0); glVertex2f(mx,my + 15);
	glTexCoord2f(1.0, 0.0); glVertex2f(mx,my);
	glEnd();*/
}