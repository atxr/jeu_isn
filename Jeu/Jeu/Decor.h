/*
Alors ici la classe Decor

mmm la ya du monde

ca gere la map en gros et le backgound

le decor quoi..
*/

#pragma once
#include <SFML\Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "typedef.h"

class Decor
{
public:
	Decor(); //Constructeur 
	~Decor(); //Destructeur
	void loadMap(int const level, sf::RenderWindow &window); //Ca cest la fonction qui charge la map et la met dans un tableau puis la dessine sur lecran 
	void testCollision(Mouvement * mouvement); //Et ca cest ce qui permet de tester si le personnage rentre en collision avec la map
private:

	std::vector<std::vector<int>> map; // ca cest un tableau de tableau de int :o en gros tableau a 2 dimensions mdrr dedans on met la map

	sf::Texture tileTexture; //La cest la texture de la map quon va decouper en sprite ensuite
	sf::Sprite tileSprite; //Et le fameux sprite

	sf::Texture backgroundTexture; //Pareil pour le background quon devrait changer ptet celui la est provisoire
	sf::Sprite background; //Encore le fameux sprite qui va avec :o

	int MAP_SIZE_X; //Ici le nombre de bloc qu'on met en longeur
	int MAP_SIZE_Y; //Et la en largeur. Cest 2 valeurs vont changer quand on aura la map pour linstant jai mis au hasard hein ce qui explique que la map est coup�

	enum : int { TRANSPARANT, TERRE, TERRE_GAZON, ROCHE, ROCHE_GAZON, ECHELLE }; //Ca cest une sorte de tableau de int en gros transparent = 0, terre = 1 ...

																				 //CONSTANTES

	const int TILE_SIZE = 32; //La taille des petits sprites en pixels il me semble sur notre texture

	int TRANSPARANT_X = 0 * TILE_SIZE; //et ca cest la position des sprites sur la texure
	int TRANSPARANT_Y = 0 * TILE_SIZE; //Cest des coordon�es en fait
	int TERRE_X = 3 * TILE_SIZE; //Voila la cest la meme mais pour la terre 
	int TERRE_GAZON_X = 2 * TILE_SIZE; //etc...
	int ROCHE_X = 5 * TILE_SIZE;
	int ROCHE_GAZON_X = 4 * TILE_SIZE;
	int TERRE_ET_ROCHE_Y = 11 * TILE_SIZE;
	int ECHELLE_X = 5 * TILE_SIZE;
	int ECHELLE_Y = 5 * TILE_SIZE;

};

