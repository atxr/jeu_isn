/*
main.cpp

je me contente de creer et d'initilaliser certains truc et de faire la boucle de jeu et le dessin et pouff le tour et jouer
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Perso.h"
#include "Hero.h"
#include "Balle.h"
#include "Decor.h"
#include "Ennemi.h"
#include <math.h>
#include <istream>

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

	int score = 0;
	bool record (false);
	int nbEnnemi (0);
	bool lecture = false;

	//Parametres de la fenetre
	int const width = 1100;
	int const height = 640;
	sf::RenderWindow window(VideoMode(width, height), "Hello World!");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	sf::View view;
	Vector2f positionBackground;
	Vector2f positionVie;

	//Menu

	bool menu (false);
	string pseudo;
	string mdp;

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

	Texture fondAccueilTxt;
	Sprite fondAccueil;
	
	if (!fondAccueilTxt.loadFromFile("graphics/fond.png"))
	{
		cout << "Erreur";
	}

	else
	{
		fondAccueil.setTexture(fondAccueilTxt);
		fondAccueil.setScale(0.85, 0.85);
	}

	while (window.isOpen())
	{
		window.clear();

		input.update();

		if (!menu)
		{
			Text textAccueil;
			textAccueil.setString("Catchlife Survival");
			textAccueil.setFont(font2);
			textAccueil.setCharacterSize(180);
			textAccueil.setPosition(230, 150);
			textAccueil.setFillColor(Color::Red);

			window.draw(fondAccueil);
			window.draw(textAccueil);

			if (input.getRejouer())
			{
				menu = true;
			}
		}

		else
		{
			if (!arret) //Boucle du jeu
			{
				if (!persoCharge) //Chargement des personnages sur la map
				{
					persoCharge = true;
					loadPerso(vague, &tabEnnemi, &tabHero);
				}

				time = clock.getElapsedTime(); //time prend la valeur du temps au moment du début de la boucle

				//Dessin

				if (tabHero[0]->getPosition().x <= 480)
				{
					posCentre = 480;
				}

				else
				{
					posCentre = tabHero[0]->getPosition().x;
				}

				positionBackground = Vector2f(posCentre - 480, 0); //Scrolling du background
				positionVie = Vector2f(posCentre + 280, 0); //Position des vies

				background.setPosition(positionBackground - Vector2f(10, 0)); // on le decale de 10px vers la gauche pour eviter les beugs
				window.draw(background); //Dessin du background

				decor.loadMap(&window); //On dessine la map

				tabHero[0]->updatePerso(&input, &decor, time); //On met a jour le hero
				tabHero[0]->dessinerPerso(&window); //Dessin du hero et de ses balles

				for (int i = 0; i < tabEnnemi.size(); i++)
				{
					tabEnnemi[i]->updatePerso(&decor, tabHero[0]->getPosition()); //On met a jour les ennemis
					tabEnnemi[i]->dessinerPerso(&window); //Dessin des ennemmis et de leurs balles

					if (tabHero[0]->testBalle(tabEnnemi[i])) //On detruit les ennemis si jamais ils sont tués
					{
						delete tabEnnemi[i];
						tabEnnemi.erase(tabEnnemi.begin() + i);

						if (tabEnnemi.size() == 0) //Si tous les ennemis sont morts, on change de vague	
						{
							vague++;
							loadPerso(vague, &tabEnnemi);
						}

						nbEnnemi++;
					}

					if (tabEnnemi[i]->testBalle(tabHero[0])) //Si jamais le héro est touché par une balle...
					{
						if (tabHero[0]->estMort()) //On regarde si il est encore en vie
						{
							arret = true; //Si il est mort on quitte la boucle du jeu
							compteurFin.restart();
						}
					}
				}

				decor.drawLife(&window, tabHero[0]->getVie(), positionVie); //Dessin des vies

				view.reset(FloatRect(positionBackground, Vector2f(864, 480))); //On établie la vue

				window.setView(view);
			}

			else
			{
				score = ceil(100 * nbEnnemi + 100 * nbEnnemi / time.asSeconds()); //On calcul le score

				//On lit le fichier score et on regarde si le score est un reccord. Si jamais c'est un reccord on remplace la valeur dans le fichier.
				if (!lecture)
				{
					ifstream fichierScore("score.txt", ios::in);
					if (fichierScore)
					{
						string buffer;
						getline(fichierScore, buffer);
						int meilleurScore = stoi(buffer);
						fichierScore.close();

						if (meilleurScore < score)
						{
							ofstream fichierScore1("score.txt", ios::out | ios::trunc);

							if (fichierScore1)
							{
								fichierScore1 << score;
								fichierScore1.close();
							}

							else
							{
								cerr << "Erreur lors de l'ouverture du fichier score";
							}

							record = true;
						}
					}

					else
					{
						cerr << "Erreur lors de l'ouverture du fichier score";
					}

					lecture = true;
				}

				view.reset(FloatRect(Vector2f(), Vector2f(864, 480)));
				window.setView(view);

				stringstream strScore;
				strScore << "Votre score est de : " << score;
				textScore.setString(strScore.str());

				if (record) //Si c'est un reccord on affiche "Nouveau reccord !"
				{
					window.draw(textRecord);
				}

				window.draw(textGameOver); //On dessine les textes
				window.draw(textScore);

				if (input.getRejouer() && compteurFin.getElapsedTime().asSeconds() > 1) //Si jamais une touche est pressée alors on reinitailise le jeu et on relance la boucle de jeu
				{
					arret = false;
					tabEnnemi.clear();
					tabHero.clear();
					persoCharge = false;
					nbEnnemi = 0;
					clock.restart();
				}
			}
		}

		window.display();

	}

	return 0;
}