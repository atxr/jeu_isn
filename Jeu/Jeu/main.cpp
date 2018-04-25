/* TADAAA VOICI NOTRE PETIT JEU
ALOOOORS PETIT RECPITUlaTIF DE CE QUI EST FAIT ET PAS FAIT:

ACTUELEMENT JE SUIS EN TRAIN DE FAIRE LES MOUVEMENTS DU PERSO C'EST PAS FINI YA PLEIN DE BEUG HEIN POUR LA GRAVITé ET LE SAUT NOTAMMENT
EN PRINCIPE DROITE - GAUCHE ET LES COLISIONS CEST BON TU ME DIS SI TU TROUVE DES BEUG DANS LE JEU

ENSUITE COMME TU PEUX LE VOIR YA UN DEBUT DE MAP
LE FICHIER QUI DESSINE LA MAP S'APPELLE level1.txt JE CROIS CHAQUE NUMERO CORRESPOND A UNE TILE PRECISE (TOUT EST PRECISé DANS DECOR.CPP)
BREF DONC IL NOUS FAUDRAIT UNE MAP CE SERAIT COOL DEJA

ENSUITE LE TIR EST BEUG2 DE FOU
JAVAIS FAIT UN PROTOYPE QUE JE VAIS REPRENDRE EN ENTIER DONC LAISSE LE MOI CE PETIT FDP DE TIR LA MDRRRR

COMME TU LE VOIS CA NOUS LAISSE LA CLASSE ENNEMI QUI EST PRESQUE VIERGE JE CROIS
CE SERAIT COOL QUE TU COMMENCE A Y REFLECHIR PAS FORCEMENT A LA PROGRAMMER SI TES PAS A LAISE EN C++ MAIS AU MOINS A REFLECHIR COMMENT ON VA SE DEBROUILLER POUR
FAIRE NOTRE "MINI INTELLIGENCE ARTIFIELLE" PAS TROP INTELLIGENTE POUR LES MECHANTS

ENFIIN IL ME RESTE UN PETIT TRUC A REGLER: LE PERSOOOOOO
ET OUI COMME TU PEUX LE CONSTATER ON A UN BEAU RECTANGLE ROUGE POUR LINSTANT ET C'EST PAS OUF JE DOIS ADMETTRE DONC IL NOUS FAUDRAIT UNE SPRITESHEET D'UN PERSO SI
POSSIBLE
D'AILLEURS TEN PENSE QUOI DE LA TEXTURE, MOI J'AIME BIEN PERSO :D

JE TE FAIT UNE PETITE PERSENTATION DE CHAQUE CLASSE AU DEBUT DE CHAQUE FICHIER POUR QUE TU TY RETROUVE UN PEU

DERNIER TRUC FAUDRAIT QUON SE METTE DACCORD SUR GITHUB POUR SAVOIR SI ON TRAVAILLE SUR 1 SEUL FICHIER OU SUR 2 ET QUON MET EN COMMUN QD ON A DES AMELIORATIONS...
BREF TA COMPRIS

VOILAAAA DIS MOI SI TA LE MOINDRE PB

ET POUR FINIR JE SUIS EN TRAIN DE NETOYER LE CODE DONC YA PAS MAL DE TRUC BIZZARD HEIN MAIS JE TE DIRAIS QD JAURAIS TOUT BIEN NETOOYER

IL NOUS FAUDRAIT UN NOM AUSSI 
*/


/*
main.cpp

alors ici cest pas nettoyer mais en principe il va pas se passer grand chose pcq tout ou presque va se faire dans les classes

je me contente de creer et d'initilaliser certains truc et de faire la boucle de jeu et le dessin et pouff le tour et jouer

bref tatarde pas trop ici cest un peu sale :o
*/

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Perso.h"
#include "Balles.h"
#include "Decor.h"
#include "Ennemi.h"
#include <math.h>

int main()
{
	//////////////////////////////////////////////////////////////////////

	//Initialisation des parametres de base

	//Parametres de la fenetre
	sf::RenderWindow window({ 800,480 }, "Hello World!"); //GRAVITE ATTENTION DECOR.CPP
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	//Horloge
	sf::Clock clock;
	float time;

	//Perso
	Perso rect;
	bool position(true); //Vers la droite par défaut si "true"

	//Saut
	bool sauter(false);
	float tempsDebutSaut;
	bool tomberDebut(false);
	bool tomber(false);
	float tempsDebutTomber;

	//Balles
	bool tir(false);
	bool update;
	std::vector<Balles*> vecBalles;

	//Decor
	Decor decor;

	//Input
	Input input(&window);

	///////////////////////////////////////////////////////////////////////////

	//Boucle de jeu


	while (window.isOpen())
	{
		time = clock.getElapsedTime().asMilliseconds(); //time prend la valeur du temps au moment du début de la boucle


		/////////////////////////////////////////////////////////////////////////////////

		//Evenements

		input.update();

		/////////////////////////////////////////////////////////////////////////////////

		//Map


		/////////////////////////////////////////////////////////////////////////////////

		//Evenements

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sauter) //Initialisation du saut
		{
			sauter = true;
			tempsDebutSaut = clock.getElapsedTime().asMilliseconds();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) //Tir
		{
			int a = vecBalles.size() - 1;

			if (!tir)
			{
				tir = true;
				vecBalles.push_back(new Balles(rect.getPosition(), time, position));
			}

			else if (time - vecBalles[a]->getTempsDebut() > 200)
				tir = false;
		}

		/////////////////////////////////////////////////////////////////////////////////

		//Mouvements

		if (sauter) //Saut
		{
			sauter = rect.sauter(time - tempsDebutSaut);

			if (!sauter)
				tomberDebut = true;
		}

		else if (tomberDebut) //Chute
		{
			tempsDebutTomber = time;
			tomberDebut = false;
			tomber = true;
		}

		if (tomber)
		{
			//rect.tomber(vecPositionDecor,vecDecorSolide);
		}

		/////////////////////////////////////////////////////////////////////////////////

		//Dessin


		window.clear();

		decor.loadMap(1, window);

		rect.update(&input, &decor);

		window.draw(rect); //Dessin du perso

		for (int i = 0; i < vecBalles.size(); i++)
		{
			update = vecBalles[i]->update(time);

			if (update)
				window.draw(*vecBalles[i]);

			else
				vecBalles.erase(vecBalles.begin() + i);
		}

		window.display();
	}
}