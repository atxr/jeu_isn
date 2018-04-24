#include "Balles.h"

int Balles::compteur = 0;

Balles::Balles()
{
}

Balles::Balles(sf::Vector2f const a, float const temps, bool const dir) : sf::RectangleShape::RectangleShape(sf::Vector2f(15, 5)), m_tempsDebut(temps), m_direction(dir)
{
	++compteur;

	setFillColor(sf::Color::Yellow);
	setPosition(a + sf::Vector2f(0, 20));
}


Balles::~Balles()
{
	--compteur;
}


int Balles::getCompteur()
{
	return compteur;
}

bool Balles::update(float const temps)
{
	if (temps - m_tempsDebut > 500)
		return false;

	if (m_direction)
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
