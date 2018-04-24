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

class Perso : public sf::RectangleShape
{
public:
	Perso(); //Constructeur -> ce que l'ont fait quand on creer un nouveau perso
	~Perso(); //Destructeur -> ce que l'ont fait quand on detruit un  perso, je men sert pas met il est la par defaut alors pour linstant je le laisse il gene pas
	void avancer(); //Ca je vais supprimer fait pas attention
	void reculer(); //Ca aussi
	bool sauter(float x); //Ca de meme
	bool tomber(vector<int> map, vector<Vector2f*> vecPositionDecor); // ca egallement
	void update(Input *input, Decor *decor); // CA NAAAN on garde mdrr cest ce qui permet de faire avancer reculer bouger tester les collision etc..
private:
	int m_vie; //La vie du perso pour linstant comme ya pas dennemi elle sert a rien un peu
	Mouvement *mouvement; //Ca c'est une structure (regroupement de variables dans un type qui sappelle mouvement) qui teste les collisions (voir typedef.h)
	Bouton bouton; //Et ca une autre structure qui permet de savoir quelle entrée du clavier est appuyé etc (voir typedef.h et aussi la classe Input)
};

