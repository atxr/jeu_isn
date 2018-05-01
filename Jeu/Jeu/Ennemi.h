/*
La classe ennemi ... vide ...
*/

#pragma once
#include <SFML\Graphics.hpp>
#include "Perso.h"

class Ennemi : public Perso
{
public:
	Ennemi();
	Ennemi(int x, int y);
	virtual void updatePerso(Input *input, Decor *decor, Time time);
	~Ennemi();
};

