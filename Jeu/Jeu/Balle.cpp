#include "Balle.h"



Balle::Balle()
{
}

Balle::Balle(sf::Vector2f const a, bool dir) : sf::RectangleShape::RectangleShape(sf::Vector2f(15, 5)), direction(dir) //ATTENTION TEST BALLE LIE
{
	setFillColor(sf::Color::Yellow);
	setPosition(a + sf::Vector2f(0, 20)); //ATTENTION TEST DE VISEE DE DECOR LIE A CA
}


Balle::~Balle()
{
}

bool Balle::update()
{
	if (dureeVie.getElapsedTime().asSeconds() > 0.5)
	{
		return false;
	}

	else if (direction)
	{
		setPosition(getPosition() + sf::Vector2f(VITESSE, 0));
		return true;
	}

	else
	{
		setPosition(getPosition() - sf::Vector2f(VITESSE, 0));
		return true;
	}
}

bool Balle::getDirection()
{
	return direction;
}

void Balle::getCollision(Collision * test)
{
	test->longueur = 15;
	test->hauteur = 5;
	test->position = getPosition();
	test->valeur = 0;
	test->statut = false;

	if (direction)
	{
		test->vitesse = VITESSE;
	}
	else
	{
		test->vitesse = -VITESSE;
	}
}
