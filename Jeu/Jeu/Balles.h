/*
La classe Balles qui gere les balles mdrrr
Euu ba celle la ca sert a rien de regarder je vais la refaire toute facon
*/

#pragma once
#include <SFML\Graphics.hpp>

class Balles : public sf::RectangleShape
{
public:
	Balles();
	Balles(sf::Vector2f const position, float const temps, bool const dir);
	~Balles();
	static int getCompteur();
	bool update(float const temps);
	float getTempsDebut();
private:
	static int compteur;
	bool m_direction;
	float m_tempsDebut;
	float m_alea;
};

