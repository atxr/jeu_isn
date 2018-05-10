/*
La classe ennemi ... vide ...
*/

#pragma once
#include <SFML\Graphics.hpp>
#include "Perso.h"
#include <ctime>
#include <cstdlib>
#include <cmath>

class Ennemi : public Perso
{
public:
	Ennemi();
	Ennemi(int x, int y);
	void updatePerso(Decor *decor, Vector2f positionHero);
	~Ennemi();
private:
	int action;
	bool occupe;
	bool pause;
	bool finFeu;
	bool pauseFeu;
	Clock chronoAction;
	bool direction;
	Clock chronoFeu;

	enum : int {ATTENDRE, AVANCER_DROITE, AVANCER_GAUCHE};
};

