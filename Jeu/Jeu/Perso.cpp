#include "Perso.h"
#include <iostream>


Perso::Perso() : RectangleShape::RectangleShape(Vector2f(25, 40)), feu(false), mort(false) //Attention la taille est dans la fonctioon update et la fonction getEchelle
{
}


Perso::~Perso()
{
}


void Perso::dessinerPerso(RenderWindow * window)
{
	window->draw(*this);

	for (int i = 0; i < tabBalle.size(); i++)
	{
		window->draw(*tabBalle[i]);
	}
}

void Perso::recevoirDegat(int degat)
{
	m_vie -= degat;

	if (m_vie < 0)
	{
		mort = true;
	}
}

