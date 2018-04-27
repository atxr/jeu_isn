#include "Perso.h"
#include <iostream>


Perso::Perso() : RectangleShape::RectangleShape(Vector2f(25, 40)) //Attention la taille est dans la fonctioon update
{
	setFillColor(Color::Red);
	setPosition(120, 400);

	sol = false;
}


Perso::~Perso()
{
}


void Perso::avancer()
{
	setPosition(Vector2f(getPosition() + Vector2f(2, 0)));
}


void Perso::reculer()
{
	setPosition(Vector2f(getPosition() + Vector2f(-2, 0)));
}


bool Perso::sauter(float x)
{
	float f = 13 * (0.002*x - 0.5); //-5 * (2x -1)
	setPosition(Vector2f(getPosition() + Vector2f(0, f)));
	return f > 0;
}

bool Perso::tomber(vector<int> map, vector<Vector2f*> vecPositionDecor)
{


	return false;
}

void Perso::update(Input *input, Decor *decor, Time time)
{
	mouvement = new Mouvement;
	mouvement->bas = mouvement->droite = mouvement->gauche = mouvement->haut = false;
	mouvement->position = getPosition();
	decor->testCollision(mouvement);

	bouton.droite = input->getStatut(DROITE);
	bouton.gauche = input->getStatut(GAUCHE);
	bouton.haut = input->getStatut(HAUT);
	bouton.bas = input->getStatut(BAS);
	bouton.attaque = input->getStatut(ATTAQUE);
	bouton.pause = input->getStatut(PAUSE);

	if (bouton.droite) //DROITE
	{
		if (mouvement->droite)
		{
			setPosition(getPosition() + Vector2f(2, 0));
		}
		else
		{
			setPosition(Vector2f(mouvement->maxDroite, getPosition().y));
		}
	}

	if (bouton.gauche) //GAUCHE
	{
		if (mouvement->gauche)
		{
			setPosition(getPosition() - Vector2f(2, 0));
		}
		else if (mouvement->maxGauche == 0)
		{
			setPosition(Vector2f(0, getPosition().y));
		}
	}

	if (mouvement->bas) //TOMBER
	{
		setPosition(getPosition() + Vector2f(0, 4));
		sol = false;
	}
	else
	{
		setPosition(Vector2f(getPosition().x, mouvement->maxBas));
		sol = true;
	}

	if (bouton.haut && sol) //SAUTER
	{
		saut = true;
		debutSaut = time;
	}

	if (saut)
	{
		if (time.asSeconds()- debutSaut.asSeconds() < 0.5)
		{
			float f = 11 - 22 *(time.asSeconds() - debutSaut.asSeconds());
			setPosition(getPosition() - Vector2f(0, f));
		}

		else
		{
			saut = false;
		}

	}

	if (bouton.bas) //SE BAISSER
	{

	}

	//ICI CEST PAS FINI COMME TU PEUX LE VOIR

	delete mouvement;
}
