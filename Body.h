#pragma once
class RuinesMap;

class Body
{
public:
	Body();
	Body(int lvl, RuinesMap &_rm);// получает в качестве параметра левел на котором √√, что бы расчитать статы мобов.
	Body(int lvl, RuinesMap*_rm);
	~Body();
	Body(const Body&rhs);
	void operator=(Body&rhs);
	void NewMapMan(); // отвечает за выбор места дл€ жизы на мапе
	int move(int x, int y); // по сути,  сейчас сделаю что бы эта шл€па движуху мутила
	void dMap(); //удал€ет с карты инфу по своим координатам.
	void sMap(); // ну вы пон€ли.
	void test();
	void rMove();
	void anotherMove(){};
private:
	int hp;
	int ag;
	int str;
	int intel;
	int cx;
	int cy;
	int tiktak;
	int role;
	RuinesMap * rm;
};



