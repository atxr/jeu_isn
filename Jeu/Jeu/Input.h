#pragma once
#include <SFML/Graphics.hpp>
#include "typedef.h"

class Input
{
public:
	Input(); //Constructeur mais on se sert pas de celui ci
	Input(sf::RenderWindow * window); //On se sert de lui qui prend en parametre la fenetre
	~Input(); //Destructeur
	bool getStatut(int id); //La on retourne si le bouton quon passe en parametre est enfoncé ou pas
	void setBouton(int id, bool value); //La on change la valeur du bouton quon passe en parametre
	void update(); //Et la on regarde quelle touche et enfoncé ou pas
	bool getDirection();
	bool getRejouer();
private:

	sf::Event event; //Ca cest une classe de la smfl qui gere les evenements
	sf::RenderWindow * window; //La fenetre quon passe en parametre
	Bouton bouton; //Et une structure encrore qui est dans typedef.h
	bool direction;
	bool rejouer;
};

