#pragma once

#include "Perso.h"
#include "Input.h"
#include "Decor.h"
#include <SFML\Graphics.hpp>
#include "typedef.h"

class Hero : public Perso
{
public:
	Hero();
	Hero(int x, int y);
	~Hero();
	void updatePerso(Input *input, Decor *decor, Time time); // CA on garde mdrr cest ce qui permet de faire avancer reculer bouger tester les collision
private:
	Bouton bouton; //Ca une autre structure qui permet de savoir quelle entrée du clavier est appuyé etc (voir typedef.h et aussi la classe Input)
	bool sol; //Test si le perso est sur le sol
	bool saut; //Est ce qu'on doit sauter
	Time debutSaut; //Debut tu temps auquel on a sauté
};

