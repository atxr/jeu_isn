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
	~Perso(); //Destructeur -> ce que l'ont fait quand on detruit un  perso, je men sert pas met il est la par defaut je le laisse il gene pas
	void update(Input *input, Decor *decor, Time time); // CA on garde mdrr cest ce qui permet de faire avancer reculer bouger tester les collision etc..
	void dessinerPerso(RenderWindow * window); //Dessine le perso ET les balles qui sont tir�es par ce perso
private:
	int m_vie; //La vie du perso pour linstant comme ya pas dennemi elle sert a rien un peu
	Mouvement *mouvement; //Ca c'est une structure (regroupement de variables dans un type qui sappelle mouvement) qui teste les collisions (voir typedef.h)
	Bouton bouton; //Et ca une autre structure qui permet de savoir quelle entr�e du clavier est appuy� etc (voir typedef.h et aussi la classe Input)
	bool sol; //Test si le perso est sur le sol
	bool saut; //Est ce qu'on doit sauter
	Time debutSaut; //Debut tu temps auquel on a saut�
	vector<Balle*> tabBalle; //Balles tir�es par le perso
	bool feu;
	Time debutFeu;

	//Constante

	int const GRAVITE = 4;
};

