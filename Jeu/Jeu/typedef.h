/*
typedef.h le fameux

cest un fichier ou je declare des petites structures et enum
*/

#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


// Mouvement (pour la collision)
typedef struct
{
	sf::Vector2f position;
	bool droite, gauche, haut, bas;
	float maxDroite, maxGauche, maxHaut, maxBas;
} Mouvement;


typedef struct
{
	bool statut = false;
	float valeur;
	Vector2f position;
	float longueur;
	float hauteur;
	float vitesse;
} Collision;


//Bouton (pour les boutons qui sont enfonc�s)
typedef struct
{
	bool droite, gauche, haut, bas, attaque, pause;
} Bouton;


//Et une enmeration de int: DROITE = 0, GAUCHE = 1 .....
enum : int { DROITE, GAUCHE, HAUT, BAS, ATTAQUE, PAUSE };

//Ca cest une sorte de tableau de int en gros transparent = 0, terre = 1 ...
enum : int { TRANSPARANT, ECHELLE, TERRE, TERRE_GAZON, ROCHE, ROCHE_GAZON};