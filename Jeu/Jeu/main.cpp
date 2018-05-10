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

/*ATTTENTION BEUG DE COLLISION IL FAUT RAJOUTER UN POINT DE TEST AU MILIEU DU PERSO*/

/*
main.cpp

alors ici cest pas nettoyer mais en principe il va pas se passer grand chose pcq tout ou presque va se faire dans les classes

je me contente de creer et d'initilaliser certains truc et de faire la boucle de jeu et le dessin et pouff le tour et jouer

bref tatarde pas trop ici cest un peu sale :o
*/

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Perso.h"
#include "Hero.h"
#include "Balle.h"
#include "Decor.h"
#include "Ennemi.h"
#include <math.h>

void loadPerso(vector<Hero*> * tabHero, vector<Ennemi*> * tabPerso)
{
	string fileDirPerso("level1perso");

	ifstream fichierLevelPerso(fileDirPerso);

	if (fichierLevelPerso)
	{
		int a, b, c;
		string buffer;

		for (int i = 0; i < 4; i++)
		{
			getline(fichierLevelPerso, buffer);
			istringstream iss(buffer);

			iss >> a >> b >> c;

			switch (a)
			{
			case 0:
				tabHero->push_back(new Hero(b, c));
				break;

			case 1:
				tabPerso->push_back(new Ennemi(b, c));
				break;

			case 2:
				tabPerso->push_back(new Ennemi(b, c));
				break;

			case 3:
				tabPerso->push_back(new Ennemi(b, c));
				break;

			default:
				break;

			}
		}

		fichierLevelPerso.close();
	}

	else
	{
		cerr << "Impossible d'ouvrir le fichier level." << endl;
	}
}

int main()
{
	//////////////////////////////////////////////////////////////////////

	//Initialisation

	//Parametres de la fenetre
	int const width = 960;
	int const height = 640;
	sf::RenderWindow window(VideoMode(width, height), "Hello World!"/*, Style::Fullscreen*/);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	sf::View view;
	Vector2f positionBackground;

	//Horloge
	sf::Clock clock;
	Time time;

	//Perso
	vector<Ennemi*> tabEnnemi;
	vector<Hero*> tabHero;
	bool persoCharge = false;

	//Decor
	Decor decor;

	//Input
	Input input(&window);

	Texture backgroundTexture;
	Sprite background;

	if (!backgroundTexture.loadFromFile("graphics/background.png"))
	{
		cerr << "Erreur, texture introuvable." << endl;
	}
	else
	{
		background.setTexture(backgroundTexture);
	}

	///////////////////////////////////////////////////////////////////////////

	//Boucle de jeu

	while (window.isOpen())
	{
		//Temps

		time = clock.getElapsedTime(); //time prend la valeur du temps au moment du début de la boucle

									   //Evenements

		input.update(); //On met à jour les évenements

		if (!persoCharge)
		{
			persoCharge = true;
			loadPerso(&tabHero, &tabEnnemi);
		}


		/////////////////////////////////////////////////////////////////////////////////

		//Dessin


		window.clear();

		if (tabHero[0]->getPosition().x < width / 2)
		{
			positionBackground = Vector2f(0, 0);
		}

		else
		{
			positionBackground = Vector2f(tabHero[0]->getPosition().x - 480, 0);
		}

		background.setPosition(positionBackground - Vector2f(10, 0)); // on le decale de 10px vers la gauche pour eviter les beugs
		window.draw(background);


		decor.loadMap(1, window); //On dessine la map

		tabHero[0]->updatePerso(&input, &decor, time); //On met a jour le hero
		tabHero[0]->dessinerPerso(&window); //Dessin du hero et de ses balles

		for (int i = 0; i < tabEnnemi.size(); i++)
		{
			tabEnnemi[i]->updatePerso(&decor, tabHero[0]->getPosition()); //On met a jour les ennemis
			tabEnnemi[i]->dessinerPerso(&window); //Dessin des ennemmis et de leurs balles
		}

		view.reset(FloatRect(positionBackground, Vector2f(864, 480)));

		window.setView(view);

		window.display();
	}
}