#pragma once

class GameMenu
{
public:
	GameMenu();
	~GameMenu();
	void Draw();
	int sKeyboard(unsigned char keyx, int x, int y);
	void Keyboard(unsigned char keyx, int x, int y);
};

