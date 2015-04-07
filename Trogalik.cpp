// Trogalik.cpp: определяет точку входа для консольного приложения.




#include "stdafx.h"


#include <iostream>
#include <gl\glut.h>
#include "Body.h"
#include <time.h>
#include <math.h>
#include <cstdio>
#include <stdlib.h>
#include "RuinesMap.h"
#include "Shambala.h"
#include <string.h>
#include <gl\glaux.h>
#include "TileTextures.h"
#include "GameMenu.h"

//#ifndef M_PI
#define M_PI 3.14159265

//экстернат как бы.
extern double mx;
extern double my;

extern TileTextures tails;
extern int flagMenu;
extern int flags;
extern int wWidth;
extern int wHeight;
extern Shambala x;


Shambala * xxx=&x;
int ts = 70;
int flagK;
GameMenu menu;




void Draw();
void initialize();
void Timer(int x);
void Keyboard(unsigned char keyx, int x, int y);
void SKeyboard(int keyx, int x, int y);
void MouseMove(int x, int y);		
void MouseMotin(int x, int y);
void MousePress(int button, int state, int x, int y);

int _tmain(int argc, char **argv)
{
	std::cout << "Trollguelike started" << std::endl;
	srand(time(NULL));   
	
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // два буфера, 24-битный цвет ргб
	glutInitWindowSize(wWidth, wHeight);           //Размер
	glutInitWindowPosition(100, 200);        // позиция окна.
	glutCreateWindow("Trollguelike.");      // создал окно с именем
	

	initialize();
	//glutFullScreen();
	glutSetCursor(GLUT_CURSOR_NONE);

	glViewport(0, 5000, 0, 5000);       //Отвечает за то, какая область окна перерисовывается, то есть размер такой же как у окна
	glutDisplayFunc(Draw);    //  если ты свернул приложение и развернул, вот чтобы появилась картинка, программа вызывает функцию draw, где идет отрисовка
	
	
	//
	glutTimerFunc(ts, Timer, 0);      // поясняем няшке глуту, что эту функцию юзаем для анимации
	

	glutMotionFunc(MouseMotin);			//движение с зажатой мышкой.
	glutMouseFunc(MousePress);
	glutPassiveMotionFunc(MouseMove);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SKeyboard);

	glutMainLoop();

	return 0;
}

void MouseMotin(int x, int y)
{
		//std::cout << "MouseMotin" << std::endl;
}

void MousePress(int button, int state, int x, int y)
{

		if (flagMenu == 0)
		xxx->MousePress(button, state, x, y);
	else
		std::cout << "Menu" << std::endl;


	
}

void MouseMove(int x, int y) 
{
	
	mx = x, my = wHeight-y;
	//glutWarpPointer(500, 500);
}


void initialize() //говорящее название
{

	tails.LoadTextures();
	
	glEnable(GL_TEXTURE_2D);

	//glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, wWidth, 0, wHeight);
	//glOrtho(0, wWidth, 0, wHeight, -1000, 1000);
	glMatrixMode(GL_MODELVIEW);

}

void Draw() //говорящее название
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


	if (flagMenu == 0)
		xxx->Draw();
	else
	menu.Draw();
	
	tails.DrawMouse();
	
	glutSwapBuffers(); // та же херня что и флуш, но для двойного буфера
}


void Timer(int x)
{
	
	if (flagMenu == 0)
	{
		xxx->Activ();
	}
	Draw();
	glutTimerFunc(ts, Timer, 0);
}

void SKeyboard(int keyx, int x, int y)// икс и игрик, это координаты мышки.
{// всякие ф11 и прочие юзабельные клавиши
	if (flagMenu == 0)
		xxx->sKeyboard(keyx, x, y);
	else
		menu.sKeyboard(keyx, x, y);
}

void Keyboard(unsigned char keyx, int x, int y)// икс и игрик, это координаты мышки.
{// все клавиши типа буквы цифры
	
	if (flagMenu == 0)
		xxx->Keyboard(keyx,x,y);
	else
		menu.Keyboard(keyx, x, y);
}
