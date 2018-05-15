#include "Perso.h"
#include <iostream>


Perso::Perso() 
{
}

Perso::Perso(int x, int y) : RectangleShape::RectangleShape(Vector2f(25, 40)) //Attention la taille est dans la fonctioon update et la fonction getEchelle
{
	feu = false;
	setPosition(Vector2f(x, y));
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

bool Perso::testBalle(Perso * cible)
{
	bool result (false);

	for (int i = 0; i < tabBalle.size(); i++)
	{
		if (tabBalle[i]->getDirection())
		{
			if (tabBalle[i]->getPosition().x + 15 /*longueur balle*/ > cible->getPosition().x && tabBalle[i]->getPosition().x < cible->getPosition().x + 25 /*longueur perso*/ && tabBalle[i]->getPosition().y > cible->getPosition().y && tabBalle[i]->getPosition().y + 5 /*hauteur balle*/ < cible->getPosition().y + 40 /*hauteur du perso*/)
			{
				cible->recevoirDegat(nbDegat);
				delete tabBalle[i];
				tabBalle.erase(tabBalle.begin() + i);
				result = cible->estMort();
			}
		}

		else
		{
			if (tabBalle[i]->getPosition().x < cible->getPosition().x + 25 /*longueur perso*/ && tabBalle[i]->getPosition().x + 15 /*longueur balle*/ > cible->getPosition().x && tabBalle[i]->getPosition().y > cible->getPosition().y && tabBalle[i]->getPosition().y + 5 /*hauteur balle*/ < cible->getPosition().y + 40 /*hauteur du perso*/)
			{
				cible->recevoirDegat(nbDegat);
				delete tabBalle[i];
				tabBalle.erase(tabBalle.begin() + i);
				result = cible->estMort();
			}
		}
	}

	return result;
}

bool Perso::estMort()
{
	cout << m_vie;
	return (m_vie <= 0);
}

