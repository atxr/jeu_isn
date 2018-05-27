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

void loadPerso(int vague, vector<Ennemi*> * tabPerso, vector<Hero*> * tabHero = 0)
{
	stringstream buffer;
	buffer << "level" << vague << "perso";
	string fileDirPerso = buffer.str();

	ifstream fichierLevelPerso(fileDirPerso);

	if (fichierLevelPerso)
	{
		int a, b, c;
		string buffer;

		while(getline(fichierLevelPerso, buffer)) //Tant qu'on est pas a la fin du fichier
		{
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

	bool arret (false);
	int vague = 1;

	float score (0.f);
	int nbEnnemi (0);

	//Parametres de la fenetre
	int const width = 1100;
	int const height = 640;
	sf::RenderWindow window(VideoMode(width, height), "Hello World!");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	sf::View view;
	Vector2f positionBackground;
	Vector2f positionVie;

	//Horloge
	sf::Clock clock;
	Time time;
	Clock compteurFin;

	//Perso
	vector<Ennemi*> tabEnnemi;
	vector<Hero*> tabHero;
	bool persoCharge = false;

	//Decor
	Decor decor;

	//Input
	Input input(&window);

	float posCentre;

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

	Font font1;
	if (!font1.loadFromFile("graphics/font1.ttf"))
	{
		cerr << "Erreur, police introuvable." << endl;
	}

	Font font2;
	if (!font2.loadFromFile("graphics/game_over.ttf"))
	{
		cerr << "Erreur, police introuvable." << endl;
	}

	Text textVague;
	textVague.setFont(font1);
	textVague.setFillColor(Color::Red);

	Text textRecord;
	textRecord.setFont(font2);
	textRecord.setPosition(290, 30);
	textRecord.setCharacterSize(80);
	textRecord.setFillColor(Color::Yellow);
	textRecord.setString("NOUVEAU RECORD !");

	Text textGameOver; 
	textGameOver.setFont(font2);
	textGameOver.setPosition(230, 60);
	textGameOver.setCharacterSize(200);
	textGameOver.setString("Game Over");
	textGameOver.setFillColor(Color::White);

	Text textScore;
	textScore.setFont(font2);
	textScore.setPosition(310, 300);
	textScore.setCharacterSize(60);
	textScore.setFillColor(Color::White);

	

	

	///////////////////////////////////////////////////////////////////////////

	//Boucle de jeu

	while (window.isOpen())
	{
		window.clear();

		input.update();

		if (!arret)
		{
			if (!persoCharge)
			{
				persoCharge = true;
				loadPerso(vague, &tabEnnemi, &tabHero);
			}

			//Temps

			time = clock.getElapsedTime(); //time prend la valeur du temps au moment du début de la boucle

			/////////////////////////////////////////////////////////////////////////////////

			//Dessin

			if (tabHero[0]->getPosition().x < width / 2)
			{
				posCentre = 480;
			}

			else
			{
				posCentre = tabHero[0]->getPosition().x;
			}

			positionBackground = Vector2f(posCentre - 480, 0);
			positionVie = Vector2f(posCentre + 280, 0);
			

			background.setPosition(positionBackground - Vector2f(10, 0)); // on le decale de 10px vers la gauche pour eviter les beugs
			window.draw(background);


			decor.loadMap(&window); //On dessine la map

			tabHero[0]->updatePerso(&input, &decor, time); //On met a jour le hero
			tabHero[0]->dessinerPerso(&window); //Dessin du hero et de ses balles

			for (int i = 0; i < tabEnnemi.size(); i++)
			{
				tabEnnemi[i]->updatePerso(&decor, tabHero[0]->getPosition()); //On met a jour les ennemis
				tabEnnemi[i]->dessinerPerso(&window); //Dessin des ennemmis et de leurs balles

				if (tabHero[0]->testBalle(tabEnnemi[i]))
				{
					delete tabEnnemi[i];
					tabEnnemi.erase(tabEnnemi.begin() + i);

					if (tabEnnemi.size() == 0)
					{
						vague++;
						loadPerso(vague, &tabEnnemi);
					}

					nbEnnemi++;
				}

				if (tabEnnemi[i]->testBalle(tabHero[0]))
				{
					if (tabHero[0]->estMort())
					{
						arret = true;
						compteurFin.restart();
					}
				}
			}

			decor.drawLife(&window, tabHero[0]->getVie(), positionVie);

			view.reset(FloatRect(positionBackground, Vector2f(864, 480)));

			window.setView(view);
		} 
		
		else
		{
			view.reset(FloatRect(Vector2f(), Vector2f(864, 480)));
			window.setView(view);

			score = ceil(100 * nbEnnemi + 100 * nbEnnemi  / time.asSeconds());
			stringstream strScore;
			strScore << "Votre score est de : " << score;

			textScore.setString(strScore.str());

			if (!1)
			{
				window.draw(textRecord);
			}

			window.draw(textGameOver);
			window.draw(textScore);

			if (input.getRejouer() && compteurFin.getElapsedTime().asSeconds() > 1)
			{
				arret = false;
				tabEnnemi.clear();
				tabHero.clear();
				persoCharge = false;
				nbEnnemi = 0;
				clock.restart();
			}
		}
		

		window.display();

	}

	return 0;
}