/*
Classe perso

c'est la classe du personnage comme son nom l'indique
*/

#pragma once
#include <SFML\Graphics.hpp>
#include <math.h>
#include "typedef.h"
#include "Decor.h"
#include "Input.h"
#include "Balle.h"


class Perso : public sf::RectangleShape
{
public:
	Perso(); //Constructeur -> ce que l'ont fait quand on creer un nouveau perso
	Perso(int x, int y);
	~Perso(); //Destructeur -> ce que l'ont fait quand on detruit un  perso, je men sert pas met il est la par defaut je le laisse il gene pas
	void dessinerPerso(RenderWindow * window); //Dessine le perso ET les balles qui sont tirées par ce perso
	void recevoirDegat(int degat);
	bool testBalle(Perso *cible);
	bool estMort();
protected:
	int m_vie;
	bool mort;
	Mouvement *mouvement; //Ca c'est une structure (regroupement de variables dans un type qui sappelle mouvement) qui teste les collisions (voir typedef.h)
	vector<Balle*> tabBalle; //Balles tirées par le perso
	bool feu;
	Time debutFeu;

	//Constante

	int const GRAVITE = 4;
	int nbDegat = 2;
};

