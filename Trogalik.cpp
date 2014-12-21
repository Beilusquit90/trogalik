// Trogalik.cpp: определяет точку входа для консольного приложения.


#include "stdafx.h"
#include <iostream>
#include <gl\glut.h>
#include "Body.h"
#include <time.h>
#include <stdlib.h>
#include "RuinesMap.h"
#include "Shambala.h"
#include <string.h>
#include <gl\glaux.h>
#include "TileTextures.h"




extern int flags;
Shambala * xxx;
int wWidth = 800;    //высота
int wHeight = 800;    //ширина
int ts = 70;
int flagK;
extern TileTextures tails;

//const int xSize = 15;
//const int ySize = 15;


void Draw();
void initialize();
void Timer(int x);
void Keyboard(unsigned char keyx, int x, int y);
void SKeyboard(int keyx, int x, int y);


int _tmain(int argc, char **argv)
{
	std::cout << "Trollguelike started" << std::endl;
	srand(time(NULL));   
	Shambala x;
	xxx=&x;
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // два буфера, 24-битный цвет ргб
	glutInitWindowSize(wWidth, wHeight);           //Размер
	glutInitWindowPosition(100, 200);        // позиция окна.
	glutCreateWindow("Trollguelike.");      // создал окно с именем
	

	initialize();
	//glutFullScreen();
	glViewport(0, wHeight, 0, wWidth);       //Отвечает за то, какая область окна перерисовывается, то есть размер такой же как у окна
	glutDisplayFunc(Draw);    //  если ты свернул приложение и развернул, вот чтобы появилась картинка, программа вызывает функцию draw, где идет отрисовка
	glutTimerFunc(ts, Timer, 0);      // поясняем няшке глуту, что эту функцию юзаем для анимации

	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SKeyboard);

	glutMainLoop();
	return 0;
}



void initialize() //говорящее название
{

	tails.LoadTextures();
	
	glEnable(GL_TEXTURE_2D);
	
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, wWidth, 0, wHeight);
	glMatrixMode(GL_MODELVIEW);
}

void Draw() //говорящее название
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	xxx->Draw();
	glLoadIdentity();
	glutSwapBuffers(); // та же херня что и флуш, но для двойного буфера
}


void Timer(int x)
{
	xxx->Activ();
	Draw();
	glutTimerFunc(ts, Timer, 0);
}

void SKeyboard(int keyx, int x, int y)// икс и игрик, это координаты мышки.
{// всякие ф11 и прочие юзабельные клавиши
	if (flags == 0)
	{
		switch (keyx)
		{
		case GLUT_KEY_LEFT: if (flags == 0){ flags = 3; }	break;	//влево
		case GLUT_KEY_RIGHT:if (flags == 0){ flags = 1; }	break;	//вправо
		case GLUT_KEY_DOWN:	if (flags == 0){ flags = 4; }	break;	//вниз
		case GLUT_KEY_UP:	if (flags == 0){ flags = 2; }	break;	//вверх
		}
	}
}

void Keyboard(unsigned char keyx, int x, int y)// икс и игрик, это координаты мышки.
{// все клавиши типа буквы цифры
	if (flags == 0)
	{
		switch (keyx)
		{
		case 'a':	if (flags == 0){ flags = 5; }	break;	//влево
		//case 'd':	//if (key != 3){ key = 4; }	break;	//вправо
		//case 's':	//if (key != 1){ key = 2; }	break;	//вниз
		//case 'w':	//if (key != 2){ key = 1; }	break;	//вверх
		//case '=':	//if (ts>10){ ts--; cout << ts << endl; }	break;	//++
		//case '-':	//ts++; cout << ts << endl;	break;	//--
		//case '9':	//ap++;;	break;	//++
		//case '0':	//ap--;;	break;	//--
		}
		//flagk = 1;
	}
}
