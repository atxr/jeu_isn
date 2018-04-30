#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include "typedef.h"


class Balle : public RectangleShape
{
public:
	Balle();
	Balle(Vector2f const position, bool const dir);
	~Balle();
	bool update();
	bool getDirection();
	void getCollision(Collision *test);
private:
	bool direction;
	Clock dureeVie;

	//Constante

	int VITESSE = 15;
};

