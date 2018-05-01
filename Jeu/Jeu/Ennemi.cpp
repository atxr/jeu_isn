#include "Ennemi.h"



Ennemi::Ennemi()
{
}

Ennemi::Ennemi(int x, int y) : Perso(x,y)
{
	setFillColor(Color::Blue);
}

void Ennemi::updatePerso(Input * input, Decor * decor, Time time)
{
	Collision * test = new Collision;

	test->longueur = 25;
	test->hauteur = 40;
	test->position = getPosition();
	test->vitesse = 2;

	test->vitesse = GRAVITE;

	decor->testCollisionBas(test);

	if (test->statut)
	{
		setPosition(getPosition() + Vector2f(0, GRAVITE));
	}

	else
	{
		setPosition(Vector2f(getPosition().x, test->valeur));
	}

	test->position = getPosition();
	test->statut = false;
	test->valeur = 0;
}


Ennemi::~Ennemi()
{
}
