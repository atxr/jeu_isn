#include "Balles.h"

int Balles::compteur = 0;

Balles::Balles()
{
}

Balles::Balles(sf::Vector2f const a, bool dir) : sf::RectangleShape::RectangleShape(sf::Vector2f(15, 5)), direction(dir)
{
	++compteur;

	setFillColor(sf::Color::Yellow);
	setPosition(a + sf::Vector2f(0, 20));

	std::cout << 1;
}


Balles::~Balles()
{
	--compteur;
}


int Balles::getCompteur()
{
	return compteur;
}

bool Balles::update()
{
	if (dureeVie.getElapsedTime().asSeconds() > 0.5)
	{
		return false;
	}

	else if (direction)
	{
		setPosition(getPosition() + sf::Vector2f(15, 0));
		return true;
	}

	else
	{
		setPosition(getPosition() - sf::Vector2f(15, 0));
		return true;
	}
}

float Balles::getTempsDebut()
{
	return m_tempsDebut;
}
