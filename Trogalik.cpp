// Trogalik.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>
#include <gl\glut.h>
#include "Body.h"
#include <time.h>
#include <stdlib.h>
#include "RuinesMap.h"
#include "Shambala.h"


Shambala * xxx;
int wWidth = 800;    //������
int wHeight = 800;    //������
int ts = 300;
//const int xSize = 15;
//const int ySize = 15;

void Draw();
void initialize();
void Timer(int x);


int _tmain(int argc, char **argv)
{
	srand(time(NULL));   
	//RuinesMap x(1);
	Shambala x;
	xxx=&x;
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // ��� ������, 24-������ ���� ���
	glutInitWindowSize(wWidth, wHeight);           //������
	glutInitWindowPosition(100, 200);        // ������� ����.
	glutCreateWindow("Trollguelike.");      // ������ ���� � ������
	initialize();

	glViewport(0, wHeight, 0, wWidth);       //�������� �� ��, ����� ������� ���� ����������������, �� ���� ������ ����� �� ��� � ����
	glutDisplayFunc(Draw);    //  ���� �� ������� ���������� � ���������, ��� ����� ��������� ��������, ��������� �������� ������� draw, ��� ���� ���������
	glutTimerFunc(ts, Timer, 0);      // �������� ����� �����, ��� ��� ������� ����� ��� ��������

//	glutKeyboardFunc(Keyboard);
//	glutSpecialFunc(SKeyboard);

	glutMainLoop();
	return 0;
}



void initialize() //��������� ��������
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, wWidth, 0, wHeight);
	glMatrixMode(GL_MODELVIEW);
}

void Draw() //��������� ��������
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	//  Setka();
	xxx->Draw();
	glLoadIdentity();
	glutSwapBuffers(); // �� �� ����� ��� � ����, �� ��� �������� ������
}

void Timer(int x)
{
	xxx->Activ();
	Draw();
	glutTimerFunc(ts, Timer, 0);
}